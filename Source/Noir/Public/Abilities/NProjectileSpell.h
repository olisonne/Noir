// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NDamageGameplayAbility.h"
#include "Abilities/NGameplayAbility.h"
#include "NProjectileSpell.generated.h"

class UGameplayEffect;
class ANProjectile;
UCLASS()
class NOIR_API UNProjectileSpell : public UNDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ANProjectile> ProjectileClass;
};
