// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/NPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilitySpec.h"
#include "MVVMGameSubsystem.h"
#include "AbilitySystem/NAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Interface/NModel.h"
#include "Player/NPlayerState.h"
#include "Input/NInputComponent.h"
#include "UI/WidgetComponent/DamageTextComponent.h"

ANPlayerController::ANPlayerController()
{
	bReplicates = true;
}

void ANPlayerController::ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if(IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void ANPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DefaultMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	TurnRateGamepad = 50.f;
	ControlledPawn = GetPawn<APawn>();
}

void ANPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if(EnhancedInputComponent)
	{
		if (MoveForwardInputAction)
		{
			EnhancedInputComponent->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ANPlayerController::OnMoveForwardAction);
		}

		if (MoveSideInputAction)
		{
			EnhancedInputComponent->BindAction(MoveSideInputAction, ETriggerEvent::Triggered, this, &ANPlayerController::OnMoveSideAction);
		}

		if (TurnInputAction)
		{
			EnhancedInputComponent->BindAction(TurnInputAction, ETriggerEvent::Triggered, this, &ANPlayerController::OnTurnAction);
		}

		if (LookUpInputAction)
		{
			EnhancedInputComponent->BindAction(LookUpInputAction, ETriggerEvent::Triggered, this, &ANPlayerController::OnLookUpAction);
		}

		if (JumpInputAction)
		{
			EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ANPlayerController::OnJumpActionStarted);
			EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ANPlayerController::OnJumpActionEnded);
		}

		if(OpenAttributesMenu)
		{
			EnhancedInputComponent->BindAction(OpenAttributesMenu, ETriggerEvent::Triggered, this, &ANPlayerController::OnOpenAttribueMenu);
		}
	}

	UNInputComponent* NInputcomponent = GetInputComponent();
	NInputcomponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

UNInputComponent* ANPlayerController::GetInputComponent() const
{
	return CastChecked<UNInputComponent>(InputComponent);
}

void ANPlayerController::OnPossess(APawn* InPawn)
{
	if (INModelStorage* Aggregator = Cast<INModelStorage>(InPawn))
	{
		Aggregator->InitializePRModels();
	}

	Super::OnPossess(InPawn);
}

void ANPlayerController::OnMoveForwardAction(const FInputActionValue& Value)
{
	const float Magnitude = Value.GetMagnitude();
	if (Magnitude != 0.0f && !bIsAttributeMenuOpened)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		if (ControlledPawn)
		{
			ControlledPawn->AddMovementInput(Direction, Magnitude);
		}
	}
}

void ANPlayerController::OnMoveSideAction(const FInputActionValue& Value)
{
	const float Magnitude = Value.GetMagnitude();
	if (Magnitude != 0.0f && !bIsAttributeMenuOpened)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		if (ControlledPawn)
		{
			ControlledPawn->AddMovementInput(Direction, Magnitude);
		}
	}
}

void ANPlayerController::OnTurnAction(const FInputActionValue& Value)
{
	if(!bIsAttributeMenuOpened) AddYawInput(Value.GetMagnitude() * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ANPlayerController::OnLookUpAction(const FInputActionValue& Value)
{
	if (!bIsAttributeMenuOpened )AddPitchInput(Value.GetMagnitude() * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ANPlayerController::OnJumpActionStarted(const FInputActionValue& Value)
{

}

void ANPlayerController::OnJumpActionEnded(const FInputActionValue& Value)
{

}

void ANPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void ANPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetNASC()) return;
	GetNASC()->AbilityInputTagReleased(InputTag);
}

void ANPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetNASC()) return;
	GetNASC()->AbilityInputTagHeld(InputTag);
}

UNAbilitySystemComponent* ANPlayerController::GetNASC()
{
	if(NAbilitySystemComponent == nullptr)
	{
		NAbilitySystemComponent = Cast<UNAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return NAbilitySystemComponent;
}
