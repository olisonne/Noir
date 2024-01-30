// Fill out your copyright notice in the Description page of Project Settings.


#include "Charcters/NEnemy.h"

#include "GameplayTagsManager.h"
#include "AbilitySystem/NAbilityFunctionLibrary.h"
#include "AbilitySystem/NAbilitySystemComponent.h"
#include "AbilitySystem/NAttributeSet.h"
#include "AI/NAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/NEnemyWidget.h"

ANEnemy::ANEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UNAttributeSet>("AttributeSet");
}

void ANEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	AuraAIController = Cast<ANAIController>(NewController);
	AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AuraAIController->RunBehaviorTree(BehaviorTree);
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

int32 ANEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}


void ANEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}

void ANEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();


	AbilitySystemComponent->RegisterGameplayTagEvent(UGameplayTagsManager::Get().RequestGameplayTag("Effect.HitReact"), EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&ANEnemy::HitReactTagChanged
	);
}

void ANEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UNAbilityFunctionLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	Cast<UNAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void ANEnemy::InitializeDefaultAttributes() const
{
	UNAbilityFunctionLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
