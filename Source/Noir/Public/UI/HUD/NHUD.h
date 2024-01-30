// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NHUD.generated.h"

class UCommonActivatableWidget;
struct FMVVMViewModelContext;
UCLASS(BlueprintType, Blueprintable)
class NOIR_API ANHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitializeViewModels();
	virtual void PreInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ViewModels")
	TArray<FMVVMViewModelContext> ViewModelContexts;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD | CommonUI")
	UCommonUserWidget* PushWidgetToHUD(FGameplayTag Stack, TSubclassOf<UCommonActivatableWidget> WidgetClass);
};
