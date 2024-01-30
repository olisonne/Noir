// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/NAbilitySystemGlobals.h"

#include "NAbilitiyTypes.h"

FGameplayEffectContext* UNAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FNGameplayEffectContext();
}
