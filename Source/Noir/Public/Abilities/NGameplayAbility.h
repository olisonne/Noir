// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Interface/NModel.h"
#include "NGameplayAbility.generated.h"

class UNVMAbilities;

UCLASS()
class NOIR_API UNGameplayAbility : public UGameplayAbility, public INModel
{
	GENERATED_BODY()
public:

	virtual void ProcessFailActivateAbility() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	const UInputAction* GetAbilityActivationInputAction() const;

	FGameplayAbilitySpec* GetGameplayAbilitySpec() const { return GetCurrentAbilitySpec(); }

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag CurrentStatusTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag StatusTag = FGameplayTag();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbilitySpecial")
	FText AbilityDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbilitySpecial")
	bool bSpecial = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbilitySpecial")
	bool bEquippable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (DisplayName = "AbilityIcon"), Category = "GameplayAbilitySpecial|AbilityIcon")
	TSoftObjectPtr<UTexture2D> AbilityIconSoft;

	TWeakObjectPtr<UNVMAbilities> SpecialAbilitiesViewModel;

	void InitializationOfViewmodels();

	bool bBeginPlayStatusTagSet = false;

	// IModel overrides
	virtual void ResetViewModel() override;
	// End of IModel overrides

	int32 Index = INDEX_NONE;

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	FGameplayAbilityActorInfo InfoActor;
};
