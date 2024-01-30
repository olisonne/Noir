// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NProgressComponent.h"
#include "Components/NProgressComponent.h"
#include "UI/ViewModels/NVMProgress.h"
#include "MVVMGameSubsystem.h"
#include "Data/LevelUpInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UNProgressComponent::UNProgressComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	if (Implements<UNModel>())
	{
		if (INModelStorage* Aggregator = Cast<INModelStorage>(GetOuter()))
		{
			Aggregator->RegisterPRModel(this);
		}
	}
}

void UNProgressComponent::SetXPViewModel()
{
	if(ProgressViewModel)
	{
		ProgressViewModel->SetXP(XP);
	}
}

void UNProgressComponent::AddToXP(int32 InXP)
{
	XP += InXP;
	SetXPViewModel();
	SetXPPercent(XP);
}

void UNProgressComponent::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	SetLevelViewModel();
}

void UNProgressComponent::AddToAttributePoints(int32 InPoints)
{
	AttributePoints += InPoints;
	SetAttributePointsViewMode();
}

void UNProgressComponent::SetAttributePointsViewMode() const
{
	if (ProgressViewModel)
	{
		ProgressViewModel->SetAttributePoints(AttributePoints);
	}
}

void UNProgressComponent::AddToSpellPoints(int32 InPoints)
{
	SpellPoints += InPoints;
	SetSpellPointsViewMode();
}

void UNProgressComponent::SetSpellPointsViewMode() const
{
	if (ProgressViewModel)
	{
		ProgressViewModel->SetSpellPoints(SpellPoints);
	}
}

void UNProgressComponent::SetXPPercent(int32 InXP)
{
	checkf(LevelUpInfo, TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));
	const int32 CurrentLevel = LevelUpInfo->FindLevelForXP(InXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();
	if (CurrentLevel <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[CurrentLevel - 1].LevelUpRequirement;

		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = InXP - PreviousLevelUpRequirement;

		XPPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		if(ProgressViewModel)
		{
			ProgressViewModel->SetXPPercent(XPPercent);
		}
	}
}

void UNProgressComponent::SetXP(int32 InXP)
{
	XP = InXP;
	SetXPViewModel();
	SetXPPercent(XP);
}

void UNProgressComponent::SetLevelViewModel()
{
	if (ProgressViewModel)
	{
		ProgressViewModel->SetLevel(Level);
	}
}

void UNProgressComponent::SetLevel(int32 InLevel)
{
	Level = InLevel;
	SetLevelViewModel();
}

void UNProgressComponent::UpdateViewmodel()
{
	if(ProgressViewModel)
	{
		ProgressViewModel->SetLevel(Level);
		ProgressViewModel->SetXP(XP);
		ProgressViewModel->SetXPPercent(XPPercent);
	}
}

void UNProgressComponent::InitializeViewModel()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
	{
		ProgressViewModel = Cast<UNVMProgress>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMProgress::StaticClass()));
		UpdateViewmodel();
	}
}

void UNProgressComponent::ResetViewModel()
{
	ProgressViewModel = nullptr;
}


void UNProgressComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

