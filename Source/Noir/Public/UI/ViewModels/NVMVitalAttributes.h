// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NVMBase.h"
#include "NVMVitalAttributes.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNVMVitalAttributes : public UNVMBase
{
	GENERATED_BODY()

public:
//Health
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Health;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxHealth;

	void SetHealth(float NewHealth);
	void SetMaxHealth(float NewMaxHealth);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealth() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetHealthString() const;

//Mana

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Mana;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxMana;

	void SetMana(float NewMana);
	void SetMaxMana(float NewMaxMana);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetMana() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetMaxMana() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;

	UFUNCTION(BlueprintPure, FieldNotify)
	FString GetManaString() const;
};
