// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NAIController.generated.h"

class UBehaviorTreeComponent;
UCLASS()
class NOIR_API ANAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
