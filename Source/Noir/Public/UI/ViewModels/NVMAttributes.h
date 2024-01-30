// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "NVMAttributes.generated.h"

class UNVMVitalAttributes;
class UNVMPrimaryAttributes;
class UNVMSecondaryAttributes;

UCLASS()
class NOIR_API UNVMAttributes : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void InitializeViewModels();
	void ResetViewModels();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify);
	TObjectPtr<UNVMVitalAttributes> VitalAttributesViewModel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify);
	TObjectPtr<UNVMPrimaryAttributes> PrimaryAttributesViewModel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify);
	TObjectPtr<UNVMSecondaryAttributes> SecondaryAttributesViewModel;
};
