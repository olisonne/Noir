// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "NPickupWidget.generated.h"


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};


UCLASS()
class NOIR_API UNPickupWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowPickupInfo(FGameplayTag InGameplayTag);

	UFUNCTION(BlueprintCallable)
	FUIWidgetRow GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	UDataTable* PickupWidgetTable;
};
