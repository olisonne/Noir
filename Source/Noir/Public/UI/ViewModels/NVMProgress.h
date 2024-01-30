// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NVMProgress.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNVMProgress : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 Level;

	void SetLevel(int32 NewLevel);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetLevel() const;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 XP;

	void SetXP(int32 NewXP);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetXP() const;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float XPPercent;

	void SetXPPercent(float NewXPPercent);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetXPPercent() const;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 AttributePoints;

	void SetAttributePoints(int32 NewAttributePoints);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetAttributePoints() const;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 SpellPoints;

	void SetSpellPoints(int32 NewAttributePoints);

	UFUNCTION(BlueprintPure, FieldNotify)
	int32 GetSpellPoints() const;
};
