// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NGameplayTags.h"
#include "Charcters/NCharacterBase.h"
#include "Interface/CombatInterface.h"

void UNDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	if (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor) && UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)->HasAnyMatchingGameplayTags(FGameplayTagContainer(FNGameplayTags::Get().ShieldTag)))
	{
		return;
	}
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

FTaggedMontage UNDamageGameplayAbility::GetRandomTaggedMontageFromArray(
	const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[Selection];
	}

	return FTaggedMontage();
}
