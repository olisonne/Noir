// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "NEnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNEnemyWidget : public UCommonUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<APawn> OwningEnemy;
};
