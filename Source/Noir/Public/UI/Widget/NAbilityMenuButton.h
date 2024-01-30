// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "NAbilityMenuButton.generated.h"

class UNGameplayAbility;
UCLASS()
class NOIR_API UNAbilityMenuButton : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TSubclassOf<UNGameplayAbility> Ability;

	UFUNCTION(BlueprintCallable)
	void SetAbilityStatusTag(FGameplayTag StatusTag);

	UFUNCTION(BlueprintCallable)
	void SetCurrentStatusTag(FGameplayTag StatusTag);
};
