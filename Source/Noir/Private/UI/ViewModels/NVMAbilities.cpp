// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMAbilities.h"
#include "GameplayAbilitySpec.h"
#include "Abilities/NGameplayAbility.h"

void UNVMAbilities::SetSpecialAbility(FGameplayAbilitySpec* NewAbilitySpec)
{
	if (NewAbilitySpec && !SpecialAbilities.Contains(NewAbilitySpec))
	{
		if (const UNGameplayAbility* SpecialAbility = Cast<UNGameplayAbility>(NewAbilitySpec->GetPrimaryInstance()))
		{
			if(NewAbilitySpec->Ability)
			{
				SpecialAbilities.AddUnique(NewAbilitySpec);
				FSpecAbilityData AbilityData;
				AbilityData.IconSoft = SpecialAbility->AbilityIconSoft;
				AbilityData.ActivationKey = SpecialAbility->GetAbilityActivationInputAction();
				AbilityData.PrimaryAbility = SpecialAbility;
				AbilityData.StatusTag = SpecialAbility->CurrentStatusTag;

				int32 Index = SpecialAbilitiesData.AddUnique(AbilityData);

				Cast<UNGameplayAbility>(NewAbilitySpec->Ability)->Index = Index;

				UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetAbilitiesData);
			}
		}
	}
}

void UNVMAbilities::ClearSpecialAbilities()
{
	if (!SpecialAbilities.IsEmpty() || !SpecialAbilitiesData.IsEmpty())
	{
		SpecialAbilities.Empty();
		SpecialAbilitiesData.Empty();
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetAbilitiesData);
	}
}

void UNVMAbilities::ApplyAbilityCooldownBySpec(FGameplayAbilitySpec* AbilitySpec)
{
	const int32 FoundAbility = Cast<UNGameplayAbility>(AbilitySpec->Ability)->Index;
	if (FoundAbility != INDEX_NONE)
	{
		if (AbilitySpec && AbilitySpec->GetPrimaryInstance())
		{
			SpecialAbilitiesData[FoundAbility].CooldownTime = AbilitySpec->GetPrimaryInstance()->GetCooldownTimeRemaining();
		}
		SetLastAbilityTriggeredCooldown(FoundAbility);
	}
}

void UNVMAbilities::ApplyAbilityStateBySpec(FGameplayAbilitySpec* AbilitySpec)
{
	const int32 FoundAbility = Cast<UNGameplayAbility>(AbilitySpec->Ability)->Index;
	if (FoundAbility != INDEX_NONE && AbilitySpec && AbilitySpec->GetPrimaryInstance())
	{
		SpecialAbilitiesData[FoundAbility].bIsActive = AbilitySpec->GetPrimaryInstance()->IsActive();
		SetLastStatChangedAbility(FoundAbility);
	}
}

void UNVMAbilities::ApplyFailedToActivateAbility(const UNGameplayAbility* Ability)
{
	if (!Ability)
	{
		return;
	}

	const int8 FoundAbilityIndex = Ability->Index;

	if (FoundAbilityIndex != INDEX_NONE)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = SpecialAbilities[FoundAbilityIndex])
		{
			SpecialAbilitiesData[FoundAbilityIndex].bIsActive = AbilitySpec->IsActive();
			SetFailedToActivateAbility(FoundAbilityIndex);
		}
	}
}

void UNVMAbilities::SetLastAbilityTriggeredCooldown(const int32 Index)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastAbilityTriggeredCooldown, Index);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCooldown);
	LastAbilityTriggeredCooldown = INDEX_NONE;
}

void UNVMAbilities::SetLastStatChangedAbility(const int32 Index)
{
	UE_MVVM_SET_PROPERTY_VALUE(LastStatChangedAbility, Index);
	LastStatChangedAbility = INDEX_NONE;
}

void UNVMAbilities::SetFailedToActivateAbility(const int32 Index)
{
	UE_MVVM_SET_PROPERTY_VALUE(FailedToActivateAbility, Index);
	FailedToActivateAbility = INDEX_NONE;
}

float UNVMAbilities::GetCooldown()
{
	if (SpecialAbilitiesData.IsValidIndex(LastAbilityTriggeredCooldown))
	{
		return SpecialAbilitiesData[LastAbilityTriggeredCooldown].CooldownTime;
	}
	return 0.f;
}

TArray<FSpecAbilityData> UNVMAbilities::GetAbilitiesData() const
{
	return SpecialAbilitiesData;
}
