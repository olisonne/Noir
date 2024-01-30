// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMPickUp.h"

void UNVMPickUp::SetAddedGameplayTag(FGameplayTag NewGameplayTag)
{
	UE_MVVM_SET_PROPERTY_VALUE(AddedGameplayTag, NewGameplayTag);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetAddedGameplayTag);
}

FGameplayTag UNVMPickUp::GetAddedGameplayTag() const
{
	return AddedGameplayTag;
}
