// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
#include "NPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInputConfig;
class UNAbilitySystemComponent;
class UDamageTextComponent;
class UNInputComponent;

UCLASS()
class NOIR_API ANPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANPlayerController();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	float TurnRateGamepad;

	UFUNCTION()
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

	UNInputComponent* GetInputComponent() const;

	UInputConfig* GetInputConfig() const { return InputConfig; }

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenAttribueMenu();

	APawn* ControlledPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute menu")
	bool bIsAttributeMenuOpened = false;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveForwardInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveSideInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookUpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* OpenAttributesMenu;

	void OnMoveForwardAction(const FInputActionValue& Value);

	void OnMoveSideAction(const FInputActionValue& Value);

	void OnTurnAction(const FInputActionValue& Value);

	void OnLookUpAction(const FInputActionValue& Value);

	void OnJumpActionStarted(const FInputActionValue& Value);

	void OnJumpActionEnded(const FInputActionValue& Value);


	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UNAbilitySystemComponent> NAbilitySystemComponent;

	UNAbilitySystemComponent* GetNASC();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

};