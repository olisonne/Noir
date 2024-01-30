// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMProgress.h"

void UNVMProgress::SetLevel(int32 NewLevel)
{
	UE_MVVM_SET_PROPERTY_VALUE(Level, NewLevel);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetLevel);
}

int32 UNVMProgress::GetLevel() const
{
	return Level;
}

void UNVMProgress::SetXP(int32 NewXP)
{
	UE_MVVM_SET_PROPERTY_VALUE(XP, NewXP);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetXP);
}

int32 UNVMProgress::GetXP() const
{
	return XP;
}

void UNVMProgress::SetXPPercent(float NewXPPercent)
{
	UE_MVVM_SET_PROPERTY_VALUE(XPPercent, NewXPPercent);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetXPPercent);
}

float UNVMProgress::GetXPPercent() const
{
	return XPPercent;
}

void UNVMProgress::SetAttributePoints(int32 NewAttributePoints)
{
	UE_MVVM_SET_PROPERTY_VALUE(AttributePoints, NewAttributePoints);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetAttributePoints);
}

int32 UNVMProgress::GetAttributePoints() const
{
	return AttributePoints;
}

void UNVMProgress::SetSpellPoints(int32 NewAttributePoints)
{
	UE_MVVM_SET_PROPERTY_VALUE(SpellPoints, NewAttributePoints);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetSpellPoints);
}

int32 UNVMProgress::GetSpellPoints() const
{
	return SpellPoints;
}

