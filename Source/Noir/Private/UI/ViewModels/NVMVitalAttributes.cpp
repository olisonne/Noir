// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMVitalAttributes.h"

void UNVMVitalAttributes::SetHealth(float NewHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, NewHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthString);
}

void UNVMVitalAttributes::SetMaxHealth(float NewMaxHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewMaxHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxHealth);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthString);
}

float UNVMVitalAttributes::GetHealth() const
{
	return Health;
}

float UNVMVitalAttributes::GetMaxHealth() const
{
	return MaxHealth;
}

float UNVMVitalAttributes::GetHealthPercent() const
{
	return MaxHealth == 0 ? 0 : Health / MaxHealth;
}

FString UNVMVitalAttributes::GetHealthString() const
{
	return FString::SanitizeFloat(Health) + "/" + FString::SanitizeFloat(MaxHealth);
}

void UNVMVitalAttributes::SetMana(float NewMana)
{
	UE_MVVM_SET_PROPERTY_VALUE(Mana, NewMana);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMana);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaString);
}

void UNVMVitalAttributes::SetMaxMana(float NewMaxMana)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxMana, NewMaxMana);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetMaxMana);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaString);
}

float UNVMVitalAttributes::GetMana() const
{
	return Mana;
}

float UNVMVitalAttributes::GetMaxMana() const
{
	return MaxMana;
}

float UNVMVitalAttributes::GetManaPercent() const
{
	return MaxMana == 0 ? 0 : Mana / MaxMana;
}

FString UNVMVitalAttributes::GetManaString() const
{
	return FString::SanitizeFloat(Mana) + "/" + FString::SanitizeFloat(MaxMana);
}
