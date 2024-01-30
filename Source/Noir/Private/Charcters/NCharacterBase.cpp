// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/NCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "MVVMGameSubsystem.h"
#include "NGameplayTags.h"
#include "AbilitySystem/NAbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Noir/Noir.h"

#include "Player/NPlayerState.h"
#include "UI/ViewModels/NVMAbilities.h"

ANCharacterBase::ANCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	for (UObject* Model : PreInitializeCharacterModels)
	{
		CharacterModels.Add(Model);
	}

	PreInitializeCharacterModels.Reset();

	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
}

FVector ANCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FNGameplayTags& GameplayTags = FNGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_Spell))
	{
		return GetMesh()->GetSocketLocation(SpellSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Montage_Attack_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	return FVector();
}

UAbilitySystemComponent* ANCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ANCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

bool ANCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ANCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ANCharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontage;
}

UAnimMontage* ANCharacterBase::GetHealMontage_Implementation()
{
	return HealMontage;
}

UAnimMontage* ANCharacterBase::GetAOEAttackMontage_Implementation()
{
	return AOEAttackMontage;
}

void ANCharacterBase::Die()
{
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	float MontageLength = 0.f;
	if(DeathMontage)
	{
		MontageLength = PlayAnimMontage(DeathMontage);
	}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			Destroy();
		}, MontageLength, false);

	Dissolve();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

ECharacterClass ANCharacterBase::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

void ANCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANCharacterBase::InitAbilityActorInfo()
{
}

void ANCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}


void ANCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ANCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		for(int32 i = 0; i < GetMesh()->GetNumMaterials(); ++i)
		{
			GetMesh()->SetMaterial(i, DynamicMatInst);
		}
		
		StartDissolveTimeline(DynamicMatInst);
	}
}

void ANCharacterBase::AddCharacterAbilities()
{
	UNAbilitySystemComponent* NASC = CastChecked<UNAbilitySystemComponent>(AbilitySystemComponent);
	if(!HasAuthority()) return;

	NASC->AddCharacterAbilities(StartupAbilities);
	NASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void ANCharacterBase::UpdateCharacterAbilities()
{
	UNAbilitySystemComponent* NASC = CastChecked<UNAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	NASC->ClearAllAbilities();

	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (IsValid(GameInstance))
	{
		const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
		if (ViewModelSubsystem)
		{
			UNVMAbilities* SpecialAbilitiesViewModel = Cast<UNVMAbilities>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMAbilities::StaticClass()));
			if (SpecialAbilitiesViewModel)
			{
				SpecialAbilitiesViewModel->ClearSpecialAbilities();
			}
		}
	}
	NASC->AddCharacterAbilities(StartupAbilities);
}
