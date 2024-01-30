// Fill out your copyright notice in the Description page of Project Settings.


#include "NAssetManager.h"

#include "NGameplayTags.h"

UNAssetManager& UNAssetManager::Get()
{
	check(GEngine);

	UNAssetManager* NAssetManager = Cast<UNAssetManager>(GEngine->AssetManager);
	return *NAssetManager;
}

void UNAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FNGameplayTags::InitializeNativeGameplayTags();
}