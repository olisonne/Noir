// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "NGameplayTags.h"
#include "Actor/NProjectile.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UNProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UNProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
    const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
    if (!bIsServer) return;

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
    if (CombatInterface)
    {
        const FVector SocketLocation = CombatInterface->Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), FNGameplayTags::Get().Montage_Attack_Spell);
        FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
        FTransform SpawnTransform;

        SpawnTransform.SetLocation(SocketLocation);
        SpawnTransform.SetRotation(Rotation.Quaternion());
        ANProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANProjectile>(ProjectileClass, SpawnTransform,  GetAvatarActorFromActorInfo(),
            Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

        const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

        const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

        for (auto& Pair : DamageTypes)
        {
            const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
            UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
        }

    	Projectile->DamageEffectSpecHandle = SpecHandle;

    	Projectile->FinishSpawning(SpawnTransform);
    }
}
