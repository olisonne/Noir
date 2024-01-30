// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "NAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class NOIR_API UNAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UNAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
	
};
