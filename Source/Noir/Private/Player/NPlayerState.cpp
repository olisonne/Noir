// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NPlayerState.h"

#include "AbilitySystem/NAbilitySystemComponent.h"
#include "AbilitySystem/NAttributeSet.h"
#include <Net/UnrealNetwork.h>

#include "MVVMGameSubsystem.h"
#include "Components/NProgressComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ViewModels/NVMAttributes.h"
#include "UI/ViewModels/NVMProgress.h"

ANPlayerState::ANPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UNAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	ProgressComponent = CreateDefaultSubobject<UNProgressComponent>("ProgressComponent");

	AttributeSet = CreateDefaultSubobject<UNAttributeSet>("AttributeSet");

	for (UObject* Model : PreInitializeCharacterModels)
	{
		CharacterModels.Add(Model);
	}

	PreInitializeCharacterModels.Reset();
}

UAbilitySystemComponent* ANPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ANPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ANPlayerState::RegisterPRModel(UObject* Model)
{
	if (Model && Model->Implements<UNModel>())
	{
		if (!IsActorInitialized())
		{
			PreInitializeCharacterModels.Add(Model);
			return;
		}

		CharacterModels.Add(Model);
	}
}

void ANPlayerState::InitializePRModels()
{
	for (UObject* Model : CharacterModels)
	{
		if (INModel* PRModel = Cast<INModel>(Model))
		{
			PRModel->InitializeViewModel();
		}
	}
}

void ANPlayerState::ResetPRModels()
{
	for (UObject* Model : CharacterModels)
	{
		if (INModel* PRModel = Cast<INModel>(Model))
		{
			PRModel->ResetViewModel();
		}
	}
}

void ANPlayerState::AddToXP(int32 InXP)
{
	ProgressComponent->AddToXP(InXP);
	OnXPChangedDelegate.Broadcast(ProgressComponent->GetXP());
}

void ANPlayerState::AddToLevel(int32 InLevel)
{
	ProgressComponent->AddToLevel(InLevel);
	OnLevelChangedDelegate.Broadcast(ProgressComponent->GetPlayerLevel());
}

void ANPlayerState::AddToAttributePoints(int32 InPoints)
{
	ProgressComponent->AddToAttributePoints(InPoints);
}

void ANPlayerState::AddToSpellPoints(int32 InPoints)
{
	ProgressComponent->AddToSpellPoints(InPoints);
}

void ANPlayerState::SetXP(int32 InXP)
{
	ProgressComponent->SetXP(InXP);
	OnXPChangedDelegate.Broadcast(ProgressComponent->GetXP());
}

void ANPlayerState::SetLevel(int32 InLevel)
{
	ProgressComponent->SetLevel(InLevel);
	OnLevelChangedDelegate.Broadcast(ProgressComponent->GetPlayerLevel());
}

void ANPlayerState::BeginPlay()
{
	Super::BeginPlay();
	InitializePRModels();
}
