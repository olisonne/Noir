// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/NAbilityMenuButton.h"

#include "Abilities/GameplayAbility.h"
#include "Abilities/NGameplayAbility.h"

void UNAbilityMenuButton::SetAbilityStatusTag(FGameplayTag StatusTag)
{
    if (Ability)
    {
        UNGameplayAbility* AbilityInstance = Cast<UNGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
        if (AbilityInstance)
        {
            AbilityInstance->StatusTag = StatusTag;
        }
    }
}

void UNAbilityMenuButton::SetCurrentStatusTag(FGameplayTag StatusTag)
{
	if (Ability)
    {
        UNGameplayAbility* AbilityInstance = Cast<UNGameplayAbility>(Ability->GetDefaultObject<UGameplayAbility>());
        if (AbilityInstance)
        {
            AbilityInstance->CurrentStatusTag = StatusTag;
        }
    }
}

