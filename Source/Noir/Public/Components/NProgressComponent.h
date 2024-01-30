// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/NModel.h"
#include "NProgressComponent.generated.h"

class UNVMProgress;
class ULevelUpInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NOIR_API UNProgressComponent : public UActorComponent, public INModel
{
	GENERATED_BODY()

public:	
	UNProgressComponent();
	void SetXPViewModel();

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }
	FORCEINLINE int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE int32 GetSpellPoints() const { return SpellPoints; }

	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);
	void AddToAttributePoints(int32 InPoints);
	void AddToSpellPoints(int32 InPoints);

	void SetAttributePointsViewMode() const;
	void SetSpellPointsViewMode() const;

	void SetXPPercent(int32 InXP);
	void SetXP(int32 InXP);
	void SetLevelViewModel();
	void SetLevel(int32 InLevel);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNVMProgress> ProgressViewModel;

	void UpdateViewmodel();

	// IModel overrides
	virtual void InitializeViewModel() override;
	virtual void ResetViewModel() override;
	// End of IModel overrides

	ULevelUpInfo* GetLevelUpInfo() const { return LevelUpInfo; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	int32 XP = 1;

	UPROPERTY(VisibleAnywhere)
	float XPPercent = 0.f;

	UPROPERTY(VisibleAnywhere)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere)
	int32 SpellPoints = 0;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;

};
