// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/NCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/NAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Data/LevelUpInfo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/NPlayerState.h"

ANCharacter::ANCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void ANCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ANCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void ANCharacter::AddToXP_Implementation(int32 InXP)
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	NPlayerState->AddToXP(InXP);
}

void ANCharacter::LevelUp_Implementation()
{
	
}

int32 ANCharacter::GetXP_Implementation() const
{
	const ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetXP();
}

int32 ANCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	const ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetLevelUpInfo()->FindLevelForXP(InXP);
}

int32 ANCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetLevelUpInfo()->LevelUpInformation[Level].AttributePointAward;
}

int32 ANCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetLevelUpInfo()->LevelUpInformation[Level].SpellPointAward;
}

void ANCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	NPlayerState->AddToLevel(InPlayerLevel);
}

void ANCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	NPlayerState->AddToAttributePoints(InAttributePoints);
}

void ANCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	NPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 ANCharacter::GetAttributePoints_Implementation() const
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetAttributePoints();
}

int32 ANCharacter::GetSpellPoints_Implementation() const
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetSpellPoints();
}

int32 ANCharacter::GetPlayerLevel_Implementation()
{
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	return NPlayerState->GetPlayerLevel();
}

FVector ANCharacter::GetCombatPrijectileSocketLocation_Implementation()
{
	return GetMesh()->GetSocketLocation(SpellSocketName); ;
}

void ANCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	ANPlayerState* NPlayerState = GetPlayerState<ANPlayerState>();
	check(NPlayerState);
	NPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(NPlayerState, this);
	Cast<UNAbilitySystemComponent>(NPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = NPlayerState->GetAbilitySystemComponent();
	AttributeSet = NPlayerState->GetAttributeSet();

	InitializeDefaultAttributes();
}
