// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCrosshair.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FVector&, Data);

UCLASS()
class NOIR_API UTargetDataUnderCrosshair : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Task", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", DisplayName = "TargetDataUnderCrosshair"))
	static UTargetDataUnderCrosshair* CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:
	float TraceDistance = 10000.0f;
	virtual void Activate() override;
};
