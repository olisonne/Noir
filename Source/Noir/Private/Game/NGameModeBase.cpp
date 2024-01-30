// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/NGameModeBase.h"

namespace MatchState
{
	const FName Pause = FName(TEXT("Pause"));
	const FName PauseMenu = FName(TEXT("PauseMenu"));
	const FName AttributeMenu = FName(TEXT("AttributeMenu"));
	const FName GameOver = FName(TEXT("GameOver"));
}

bool ANGameModeBase::ClearPause()
{
	return (Super::ClearPause() && (SetMatchState(MatchState::InProgress), true));
}

void ANGameModeBase::OpenAttributeMenu()
{
	SetMatchState(MatchState::AttributeMenu);
}

void ANGameModeBase::OpenPauseMenu()
{
	SetMatchState(MatchState::PauseMenu);
}

void ANGameModeBase::CloseMenu()
{
	SetMatchState(MatchState::InProgress);
}

void ANGameModeBase::GameOver()
{
	SetMatchState(MatchState::GameOver);
}

void ANGameModeBase::OnMatchStateSet()
{
	Super::OnMatchStateSet();

	OnMatchStateChanged.Broadcast(MatchState);
}
