// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "Interface/NModel.h"
#include "Data/CharacterClassInfo.h"
#include "NCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;
class UBoxComponent;
class UGameplayEffect;

UCLASS(Abstract)
class NOIR_API ANCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ANCharacterBase();

	FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

	/** Combat Interface */
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	UAnimMontage* GetHealMontage_Implementation();
	UAnimMontage* GetAOEAttackMontage_Implementation();
	/** end Combat Interface */

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HealMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> AOEAttackMontage;

	virtual ECharacterClass GetCharacterClass_Implementation() override;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	virtual void InitializeDefaultAttributes() const;
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
	FName SpellSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintCallable)
	void AddCharacterAbilities();

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterAbilities();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	bool bDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defautls")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UObject>> CharacterModels;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UObject>> PreInitializeCharacterModels;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
