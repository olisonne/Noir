// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/NAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "MVVMGameSubsystem.h"
#include "Interface/NModel.h"

#include "GameFramework/Character.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/ViewModels/NVMVitalAttributes.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayEffectExtension.h"
#include "GameplayTagsManager.h"
#include "NGameplayTags.h"
#include "AbilitySystem/NAbilityFunctionLibrary.h"
#include "Interface/CombatInterface.h"
#include "Interface/NPlayerInterface.h"
#include "Player/NPlayerController.h"
#include "UI/ViewModels/NVMAttributes.h"
#include "UI/ViewModels/NVMPrimaryAttributes.h"
#include "UI/ViewModels/NVMSecondaryAttributes.h"

UNAttributeSet::UNAttributeSet()
{
	if (Implements<UNModel>())
	{
		if (INModelStorage* Aggregator = Cast<INModelStorage>(GetOuter()))
		{
			Aggregator->RegisterPRModel(this);
		}
	}

	const FNGameplayTags& GameplayTags = FNGameplayTags::Get();
	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	/* Resistance Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute);
}

void UNAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UNAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
}

void UNAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UNAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Die();
					SendXPEvent(Props);
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("Effect.HitReact"));
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			const bool bBlock = UNAbilityFunctionLibrary::IsBlockedHit(Props.EffectContextHandle);
			const bool bCriticalHit = UNAbilityFunctionLibrary::IsCriticalHit(Props.EffectContextHandle);
			ShowFloatingText(Props, LocalIncomingDamage, bBlock, bCriticalHit);
		}
	}
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		const float LocalIncomingXP = GetIncomingXP();
		SetIncomingXP(0.f);
		UE_LOG(LogTemp, Log, TEXT("Incoming XP: %f"), LocalIncomingXP);

		if (Props.SourceCharacter->Implements<UNPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
		{
			const int32 CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(Props.SourceCharacter);
			const int32 CurrentXP = INPlayerInterface::Execute_GetXP(Props.SourceCharacter);

			const int32 NewLevel = INPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP + LocalIncomingXP) + 1;
			const int32 NumLevelUps = NewLevel - CurrentLevel;
			if (NumLevelUps > 0)
			{
				const int32 AttributePointsReward = INPlayerInterface::Execute_GetAttributePointsReward(Props.SourceCharacter, CurrentLevel);
				const int32 SpellPointsReward = INPlayerInterface::Execute_GetSpellPointsReward(Props.SourceCharacter, CurrentLevel);

				INPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumLevelUps);
				INPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointsReward);
				INPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

				SetHealth(GetMaxHealth());
				SetMana(GetMaxMana());

				INPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
			}
			
			INPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
		}
	}
}

void UNAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (!AttributesViewModel) return;

	if (Attribute == GetHealthAttribute())
	{
		 AttributesViewModel->VitalAttributesViewModel->SetHealth(NewValue);
	}
	else if(Attribute == GetMaxHealthAttribute())
	{
		AttributesViewModel->VitalAttributesViewModel->SetMaxHealth(NewValue);
	}
	else if(Attribute == GetManaAttribute())
	{
		AttributesViewModel->VitalAttributesViewModel->SetMana(NewValue);
	}
	else if(Attribute == GetMaxManaAttribute())
	{
		AttributesViewModel->VitalAttributesViewModel->SetMaxMana(NewValue);
	}
	else if(Attribute == GetStrengthAttribute())
	{
		AttributesViewModel->PrimaryAttributesViewModel->SetStrength(NewValue);
	}
	else if (Attribute == GetIntelligenceAttribute())
	{
		AttributesViewModel->PrimaryAttributesViewModel->SetIntelligence(NewValue);
	}
	else if (Attribute == GetResilienceAttribute())
	{
		AttributesViewModel->PrimaryAttributesViewModel->SetResilience(NewValue);
	}
	else if (Attribute == GetVigorAttribute())
	{
		AttributesViewModel->PrimaryAttributesViewModel->SetVigor(NewValue);
	}
	else if (Attribute == GetArmorAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetArmor(NewValue);
	}
	else if (Attribute == GetArmorPenetrationAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetArmorPenetration(NewValue);
	}
	else if (Attribute == GetBlockChanceAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetBlockChance(NewValue);
	}
	else if (Attribute == GetCriticalHitChanceAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitChance(NewValue);
	}
	else if (Attribute == GetCriticalHitDamageAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitDamage(NewValue);
	}
	else if (Attribute == GetCriticalHitResistanceAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitResistance(NewValue);
	}
	else if (Attribute == GetHealthRegenerationAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetHealthRegeneration(NewValue);
	}
	else if (Attribute == GetManaRegenerationAttribute())
	{
		AttributesViewModel->SecondaryAttributesViewModel->SetManaRegeneration(NewValue);
	}
}

void UNAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Health, OldHealth);
}

void UNAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, MaxHealth, OldMaxHealth);
}

void UNAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Mana, OldMana);
}

void UNAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, MaxMana, OldMaxMana);
}

void UNAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Strength, OldStrength);
}

void UNAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Intelligence, OldIntelligence);
}

void UNAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Resilience, OldResilience);
}

void UNAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Vigor, OldVigor);
}

void UNAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, Armor, OldArmor);
}

void UNAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UNAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, BlockChance, OldBlockChance);
}

void UNAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UNAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UNAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UNAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UNAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UNAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, FireResistance, OldFireResistance);
}

void UNAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, LightningResistance, OldLightningResistance);
}

void UNAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void UNAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UNAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UNAttributeSet::UpdateViewModel()
{
	if(AttributesViewModel)
	{
		AttributesViewModel->VitalAttributesViewModel->SetHealth(GetHealth());
		AttributesViewModel->VitalAttributesViewModel->SetMaxHealth(GetMaxHealth());
		AttributesViewModel->VitalAttributesViewModel->SetMana(GetMana());
		AttributesViewModel->VitalAttributesViewModel->SetMaxMana(GetMaxMana());

		AttributesViewModel->PrimaryAttributesViewModel->SetStrength(GetStrength());
		AttributesViewModel->PrimaryAttributesViewModel->SetIntelligence(GetIntelligence());
		AttributesViewModel->PrimaryAttributesViewModel->SetResilience(GetResilience());
		AttributesViewModel->PrimaryAttributesViewModel->SetVigor(GetVigor());

		AttributesViewModel->SecondaryAttributesViewModel->SetArmor(GetArmor());
		AttributesViewModel->SecondaryAttributesViewModel->SetArmorPenetration(GetArmorPenetration());
		AttributesViewModel->SecondaryAttributesViewModel->SetBlockChance(GetBlockChance());
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitChance(GetCriticalHitChance());
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitDamage(GetCriticalHitDamage());
		AttributesViewModel->SecondaryAttributesViewModel->SetCriticalHitResistance(GetCriticalHitResistance());
		AttributesViewModel->SecondaryAttributesViewModel->SetHealthRegeneration(GetHealthRegeneration());
		AttributesViewModel->SecondaryAttributesViewModel->SetManaRegeneration(GetManaRegeneration());
	}
}

void UNAttributeSet::InitializeViewModel()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const UMVVMGameSubsystem* ViewModelSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
	{
		AttributesViewModel = Cast<UNVMAttributes>(ViewModelSubsystem->GetViewModelCollection()->FindFirstViewModelInstanceOfType(UNVMAttributes::StaticClass()));
		if(AttributesViewModel) AttributesViewModel->InitializeViewModels();
		UpdateViewModel();
	}
}

void UNAttributeSet::ResetViewModel()
{
	AttributesViewModel->ResetViewModels();
	AttributesViewModel = nullptr;
	INModel::ResetViewModel();
}

void UNAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UNAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (ANPlayerController* PC = Cast<ANPlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}
	}
}

void UNAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 XPReward = UNAbilityFunctionLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, TargetClass, TargetLevel);

		const FNGameplayTags& GameplayTags = FNGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}


