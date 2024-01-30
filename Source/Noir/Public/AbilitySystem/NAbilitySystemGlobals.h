// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "NAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
