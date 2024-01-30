// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/NAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "MVVMGameSubsystem.h"
#include "NGameplayTags.h"
#include "Abilities/NGameplayAbility.h"
#include "Interface/NPlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NPlayerState.h"
#include "UI/ViewModels/NVMPickUp.h"

UNAbilitySystemComponent::UNAbilitySystemComponent()
{
	if (Implements<UNModel>())
	{
		if (INModelStorage* Aggregator = Cast<INModelStorage>(GetOuter()))
		{
			Aggregator->RegisterPRModel(this);
		}
	}
}

void UNAbilitySystemComponent::AbilityActorInfoSet()
{
    OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UNAbilitySystemComponent::EffectApplied);
}

void UNAbilitySystemComponent::InitializeViewModel()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
	{
		PickUpViewModel = Cast<UNVMPickUp>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMPickUp::StaticClass()));
	}
}

void UNAbilitySystemComponent::ResetViewModel()
{
	INModel::ResetViewModel();
	PickUpViewModel = nullptr;
}

void UNAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for(TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if(const UNGameplayAbility* NAbility =  Cast<UNGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(NAbility->StartupInputTag);
			AbilitySpec.DynamicAbilityTags.AddTag(FNGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec);
		}
	}
}

void UNAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UNAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UNAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

bool UNAbilitySystemComponent::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	if (GetAvatarActor()->Implements<UNPlayerInterface>())
	{
		if (INPlayerInterface::Execute_GetAttributePoints(GetAvatarActor()) > 0)
		{
			FGameplayEventData Payload;
			Payload.EventTag = AttributeTag;
			Payload.EventMagnitude = 1.f;

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), AttributeTag, Payload);

			INPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(), -1);
			return true;
		}
	}
	return false;
}

bool UNAbilitySystemComponent::UpdatePoints()
{
	if (GetAvatarActor()->Implements<UNPlayerInterface>())
	{
		if (INPlayerInterface::Execute_GetSpellPoints(GetAvatarActor()) > 0)
		{
			INPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(), -1);
			return true;
		}
	}
	return false;
}

FGameplayTag UNAbilitySystemComponent::GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for(FGameplayTag StatusTag : AbilitySpec.DynamicAbilityTags)
	{
		if(StatusTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
		{
			return StatusTag;
		}
	}
	return FGameplayTag();
}

void UNAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		if(PickUpViewModel)
		{
			PickUpViewModel->SetAddedGameplayTag(Tag);
		}
	}
}
