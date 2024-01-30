// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"
#include "NVMPickUp.generated.h"

UCLASS()
class NOIR_API UNVMPickUp : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	FGameplayTag AddedGameplayTag;

	void SetAddedGameplayTag(FGameplayTag NewGameplayTag);

	UFUNCTION(BlueprintPure, FieldNotify)
	FGameplayTag GetAddedGameplayTag() const;
};
