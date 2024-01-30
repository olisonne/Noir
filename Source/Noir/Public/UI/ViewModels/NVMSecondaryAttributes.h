// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NVMBase.h"
#include "NVMSecondaryAttributes.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNVMSecondaryAttributes : public UNVMBase
{
	GENERATED_BODY()
public:

	//Armor
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float Armor;

	void SetArmor(float NewArmor);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetArmor() const;

	//ArmorPenetration
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float ArmorPenetration;

	void SetArmorPenetration(float NewArmorPenetration);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetArmorPenetration() const;

	//BlockChance
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float BlockChance;

	void SetBlockChance(float NewBlockChance);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetBlockChance() const;

	//CriticalHitChance
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CriticalHitChance;

	void SetCriticalHitChance(float NewCriticalHitChance);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetCriticalHitChance() const;

	//CriticalHitDamage
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CriticalHitDamage;

	void SetCriticalHitDamage(float NewCriticalHitDamage);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetCriticalHitDamage() const;

	//CriticalHitResistance
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CriticalHitResistance;

	void SetCriticalHitResistance(float NewCriticalHitResistance);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetCriticalHitResistance() const;

	//HealthRegeneration
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float HealthRegeneration;

	void SetHealthRegeneration(float NewHealthRegeneration);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthRegeneration() const;

	//ManaRegeneration
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float ManaRegeneration;

	void SetManaRegeneration(float NewManaRegeneration);

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaRegeneration() const;
};
