// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NVMBase.h"
#include "NVMPrimaryAttributes.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNVMPrimaryAttributes : public UNVMBase
{
	GENERATED_BODY()
public:

	//Strength
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Strength;

	void SetStrength(float NewStrength);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetStrength() const;

	//Intelligence

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Intelligence;

	void SetIntelligence(float NewIntelligence);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetIntelligence() const;

	//Resilience

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Resilience;

	void SetResilience(float NewResilience);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetResilience() const;

	//Vigor

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Vigor;

	void SetVigor(float NewVigor);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetVigor() const;
};
