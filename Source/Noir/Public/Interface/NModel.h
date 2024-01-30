// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "NModel.generated.h"

UINTERFACE(MinimalAPI)
class UNModel : public UInterface
{
	GENERATED_BODY()
};

class NOIR_API INModel
{
	GENERATED_BODY()

public:
	virtual void InitializeViewModel() {};
	virtual void ResetViewModel() {};
};

UINTERFACE(MinimalAPI)
class UNModelStorage : public UInterface
{
	GENERATED_BODY()
};

class NOIR_API INModelStorage
{
	GENERATED_BODY()

public:
	virtual void RegisterPRModel(UObject* Model) {};
	virtual void InitializePRModels() {};
	virtual void ResetPRModels() {};
};
