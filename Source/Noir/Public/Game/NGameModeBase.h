// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "NGameModeBase.generated.h"

class UCharacterClassInfo;

namespace MatchState
{
	extern NOIR_API const FName Pause;
	extern NOIR_API const FName GameOver;
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, const FName, OldMatchState);

UCLASS()
class NOIR_API ANGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(BlueprintAssignable)
	FOnMatchStateChanged OnMatchStateChanged;

	virtual bool ClearPause() override;

	UFUNCTION(BlueprintCallable)
	void OpenAttributeMenu();

	UFUNCTION(BlueprintCallable)
	void OpenPauseMenu();

	UFUNCTION(BlueprintCallable)
	void CloseMenu();

	UFUNCTION(BlueprintCallable)
	void GameOver();

protected:
	virtual void OnMatchStateSet() override;

};
