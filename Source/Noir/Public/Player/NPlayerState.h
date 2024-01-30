// Fill out your copyright notice in the Description page of Noject Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/NProgressComponent.h"
#include "GameFramework/PlayerState.h"
#include "Interface/NModel.h"
#include "NPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/)

class UAbilitySystemComponent;
class UAttributeSet;
class UNVMProgress;
class UNProgressComponent;

UCLASS()
class NOIR_API ANPlayerState : public APlayerState, public IAbilitySystemInterface, public INModelStorage
{
	GENERATED_BODY()

public:
	ANPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	ULevelUpInfo* GetLevelUpInfo() const { return ProgressComponent->GetLevelUpInfo(); }
	FORCEINLINE int32 GetAttributePoints() const { return ProgressComponent->GetAttributePoints(); }
	FORCEINLINE int32 GetSpellPoints() const { return ProgressComponent->GetSpellPoints(); }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// IPRModelStorage
	virtual void RegisterPRModel(UObject* Model) override;
	virtual void InitializePRModels() override;
	virtual void ResetPRModels() override;
	// End of IPRModelStorage

	FORCEINLINE int32 GetPlayerLevel() const { return ProgressComponent->GetPlayerLevel(); }

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;

	FORCEINLINE int32 GetXP() const { return ProgressComponent->GetXP(); }

	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);
	void AddToAttributePoints(int32 InPoints);
	void AddToSpellPoints(int32 InPoints);

	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UNProgressComponent> ProgressComponent;


private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UObject>> CharacterModels;

	UPROPERTY(Transient)
	TArray<TObjectPtr<UObject>> PreInitializeCharacterModels;


};
