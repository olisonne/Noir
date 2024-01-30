// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"
#include "NVMAbilities.generated.h"

class UInputAction;
class UNGameplayAbility;
struct FGameplayAbilitySpec;

USTRUCT(BlueprintType)
struct FSpecAbilityData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UTexture2D> IconSoft;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag StatusTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	const UInputAction* ActivationKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CooldownTime = -1.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsActive = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<const UNGameplayAbility> PrimaryAbility;

	bool operator==(const FSpecAbilityData& SpecAbilityData) const
	{
		return SpecAbilityData.IconSoft == IconSoft &&
			SpecAbilityData.ActivationKey == ActivationKey;
	}

	bool operator!=(const FSpecAbilityData& SpecAbilityData) const
	{
		return !operator==(SpecAbilityData);
	}
};

UCLASS()
class NOIR_API UNVMAbilities : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	TArray<FGameplayAbilitySpec*> SpecialAbilities;

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify)
		TArray<FSpecAbilityData> SpecialAbilitiesData;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter)
		int32 LastAbilityTriggeredCooldown = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter)
		int32 LastStatChangedAbility = INDEX_NONE;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter)
		int32 FailedToActivateAbility = INDEX_NONE;

public:
	void SetSpecialAbility(FGameplayAbilitySpec* NewAbilitySpec);
	void ClearSpecialAbilities();

	void ApplyAbilityCooldownBySpec(FGameplayAbilitySpec* AbilitySpec);
	void ApplyAbilityStateBySpec(FGameplayAbilitySpec* AbilitySpec);

	void SetLastAbilityTriggeredCooldown(const int32 Index);
	void SetLastStatChangedAbility(const int32 Index);

	void ApplyFailedToActivateAbility(const UNGameplayAbility* Ability);
	void SetFailedToActivateAbility(const int32 Index);

	UFUNCTION(BlueprintPure, FieldNotify)
		float GetCooldown();

	UFUNCTION(BlueprintPure, FieldNotify)
		TArray<FSpecAbilityData> GetAbilitiesData() const;

	
};
