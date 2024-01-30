// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModels/NVMAttributes.h"

#include "MVVMGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModels/NVMPrimaryAttributes.h"
#include "UI/ViewModels/NVMVitalAttributes.h"
#include "UI/ViewModels/NVMSecondaryAttributes.h"

void UNVMAttributes::InitializeViewModels()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
	{
		VitalAttributesViewModel = Cast<UNVMVitalAttributes>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMVitalAttributes::StaticClass()));
		PrimaryAttributesViewModel = Cast<UNVMPrimaryAttributes>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMPrimaryAttributes::StaticClass()));
		SecondaryAttributesViewModel = Cast<UNVMSecondaryAttributes>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMSecondaryAttributes::StaticClass()));
	}
}

void UNVMAttributes::ResetViewModels()
{
	VitalAttributesViewModel = nullptr;
	PrimaryAttributesViewModel = nullptr;
	SecondaryAttributesViewModel = nullptr;
}
