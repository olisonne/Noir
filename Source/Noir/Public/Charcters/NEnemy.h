// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Charcters/NCharacterBase.h"
#include "NEnemy.generated.h"

class UNAttributeSet;
class UUserWidget;
class UWidgetComponent;
class UBehaviorTree;
class ANAIController;
UCLASS()
class NOIR_API ANEnemy : public ANCharacterBase
{
	GENERATED_BODY()

public:
	ANEnemy();
	virtual void PossessedBy(AController* NewController) override;

	//Combat interface
	virtual int32 GetPlayerLevel_Implementation() override;
	//End combat interface

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 400.f;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defautls")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ANAIController> AuraAIController;
};
