// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NGameplayAbility.h"

#include "MVVMGameSubsystem.h"
#include "Input/NInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/NPlayerController.h"
#include "UI/ViewModels/NVMAbilities.h"

void UNGameplayAbility::ProcessFailActivateAbility() const
{
	if (SpecialAbilitiesViewModel.IsValid())
	{
		SpecialAbilitiesViewModel->ApplyFailedToActivateAbility(this);
	}
}

const UInputAction* UNGameplayAbility::GetAbilityActivationInputAction() const
{
	if (const ANPlayerController* PlayerController = Cast<ANPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		const UInputConfig* InputConfig = PlayerController->GetInputConfig();
		const FGameplayAbilitySpec* Spec = GetCurrentAbilitySpec();
		//const UInputMappingContext* MappingContext = PlayerInputComponent->GetDefaultMapping();
		if (InputConfig && Spec)
		{
			if (const UInputAction* InputAction = InputConfig->FindAbilityInputActionForTag(Spec->DynamicAbilityTags.First()))
			{
				return InputAction;
			}
		}
	}
	return nullptr;
}

void UNGameplayAbility::InitializationOfViewmodels()
{
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(InfoActor.AvatarActor.Get());
	if (IsValid(GameInstance))
	{
		const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
		if (ViewModelSubsystem)
		{
			SpecialAbilitiesViewModel = Cast<UNVMAbilities>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMAbilities::StaticClass()));
			if (SpecialAbilitiesViewModel.IsValid())
			{
				SpecialAbilitiesViewModel->SetSpecialAbility(GetCurrentAbilitySpec());
			}
		}
	}
}

void UNGameplayAbility::ResetViewModel()
{
	if (SpecialAbilitiesViewModel.IsValid())
	{
		SpecialAbilitiesViewModel->ClearSpecialAbilities();
	}
}

void UNGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

void UNGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (SpecialAbilitiesViewModel.IsValid())
	{
		SpecialAbilitiesViewModel->ApplyAbilityStateBySpec(GetCurrentAbilitySpec());
	}
}

void UNGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (SpecialAbilitiesViewModel.IsValid())
	{
		SpecialAbilitiesViewModel->ApplyAbilityStateBySpec(GetCurrentAbilitySpec());
	}
}

void UNGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCooldown(Handle, ActorInfo, ActivationInfo);

	if (SpecialAbilitiesViewModel.IsValid())
	{
		SpecialAbilitiesViewModel->ApplyAbilityCooldownBySpec(GetCurrentAbilitySpec());
	}
}

void UNGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if(!bSpecial) return;

	InfoActor = *ActorInfo;
	if (ActorInfo && ActorInfo->OwnerActor.IsValid())
	{
		if (INModelStorage* Aggregator = Cast<INModelStorage>(ActorInfo->OwnerActor))
		{
			Aggregator->RegisterPRModel(this);
			if (ActorInfo->IsLocallyControlledPlayer())
			{
				InitializationOfViewmodels();
			}
		}
	}
}
