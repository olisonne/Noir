// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMPrimaryAttributes.h"

void UNVMPrimaryAttributes::SetStrength(float NewStrength)
{
	UE_MVVM_SET_PROPERTY_VALUE(Strength, NewStrength);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStrength);
}

float UNVMPrimaryAttributes::GetStrength() const
{
	return Strength;
}

void UNVMPrimaryAttributes::SetIntelligence(float NewIntelligence)
{
	UE_MVVM_SET_PROPERTY_VALUE(Intelligence, NewIntelligence);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetIntelligence);
}

float UNVMPrimaryAttributes::GetIntelligence() const
{
	return Intelligence;
}

void UNVMPrimaryAttributes::SetResilience(float NewResilience)
{
	UE_MVVM_SET_PROPERTY_VALUE(Resilience, NewResilience);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetResilience);
}

float UNVMPrimaryAttributes::GetResilience() const
{
	return Resilience;
}

void UNVMPrimaryAttributes::SetVigor(float NewVigor)
{
	UE_MVVM_SET_PROPERTY_VALUE(Vigor, NewVigor);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetVigor);
}

float UNVMPrimaryAttributes::GetVigor() const
{
	return Vigor;
}
