// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Interface/NModel.h"
#include "NAbilitySystemComponent.generated.h"

class UNVMPickUp;
UCLASS()
class NOIR_API UNAbilitySystemComponent : public UAbilitySystemComponent, public INModel
{
	GENERATED_BODY()
public:

	UNAbilitySystemComponent();

	void AbilityActorInfoSet();

	TObjectPtr<UNVMPickUp> PickUpViewModel;

	// IModel overrides
	virtual void InitializeViewModel() override;
	virtual void ResetViewModel() override;
	// End of IModel overrides

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable)
	bool UpgradeAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(BlueprintCallable)
	bool UpdatePoints();

	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
