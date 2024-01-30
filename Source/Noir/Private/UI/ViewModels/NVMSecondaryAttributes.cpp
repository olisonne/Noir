// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMSecondaryAttributes.h"

void UNVMSecondaryAttributes::SetArmor(float NewArmor)
{
	UE_MVVM_SET_PROPERTY_VALUE(Armor, NewArmor);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetArmor);
}

float UNVMSecondaryAttributes::GetArmor() const
{
	return Armor;
}

void UNVMSecondaryAttributes::SetArmorPenetration(float NewArmorPenetration)
{
	UE_MVVM_SET_PROPERTY_VALUE(ArmorPenetration, NewArmorPenetration);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetArmorPenetration);
}

float UNVMSecondaryAttributes::GetArmorPenetration() const
{
	return ArmorPenetration;
}

void UNVMSecondaryAttributes::SetBlockChance(float NewBlockChance)
{
	UE_MVVM_SET_PROPERTY_VALUE(BlockChance, NewBlockChance);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetBlockChance);
}

float UNVMSecondaryAttributes::GetBlockChance() const
{
	return BlockChance;
}

void UNVMSecondaryAttributes::SetCriticalHitChance(float NewCriticalHitChance)
{
	UE_MVVM_SET_PROPERTY_VALUE(CriticalHitChance, NewCriticalHitChance);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCriticalHitChance);
}

float UNVMSecondaryAttributes::GetCriticalHitChance() const
{
	return CriticalHitChance;
}

void UNVMSecondaryAttributes::SetCriticalHitDamage(float NewCriticalHitDamage)
{
	UE_MVVM_SET_PROPERTY_VALUE(CriticalHitDamage, NewCriticalHitDamage);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCriticalHitDamage);
}

float UNVMSecondaryAttributes::GetCriticalHitDamage() const
{
	return CriticalHitDamage;
}

void UNVMSecondaryAttributes::SetCriticalHitResistance(float NewCriticalHitResistance)
{
	UE_MVVM_SET_PROPERTY_VALUE(CriticalHitResistance, NewCriticalHitResistance);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetCriticalHitResistance);
}

float UNVMSecondaryAttributes::GetCriticalHitResistance() const
{
	return CriticalHitResistance;
}

void UNVMSecondaryAttributes::SetHealthRegeneration(float NewHealthRegeneration)
{
	UE_MVVM_SET_PROPERTY_VALUE(HealthRegeneration, NewHealthRegeneration);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthRegeneration);
}

float UNVMSecondaryAttributes::GetHealthRegeneration() const
{
	return HealthRegeneration;
}

void UNVMSecondaryAttributes::SetManaRegeneration(float NewManaRegeneration)
{
	UE_MVVM_SET_PROPERTY_VALUE(ManaRegeneration, NewManaRegeneration);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaRegeneration);
}

float UNVMSecondaryAttributes::GetManaRegeneration() const
{
	return ManaRegeneration;
}
