// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/NHUD.h"
#include "MVVMGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Types/MVVMViewModelCollection.h"

void ANHUD::InitializeViewModels()
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this);
	if(!GameInstance) return;

	UMVVMGameSubsystem* VMGameSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>();
	if (!VMGameSubsystem) return;

	UMVVMViewModelCollectionObject* ViewModelCollection = VMGameSubsystem ? VMGameSubsystem->GetViewModelCollection() : nullptr;
	if (!ViewModelCollection)
	{
		return;
	}

	for (const FMVVMViewModelContext& Context : ViewModelContexts)
	{
		if (!Context.IsValid() || Context.ContextName.IsNone() || !Context.ContextClass)
		{
			continue;
		}

		if (!ViewModelCollection->FindViewModelInstance(Context))
		{
			ViewModelCollection->RemoveViewModel(Context);
			if (UMVVMViewModelBase* ViewModel = NewObject<UMVVMViewModelBase>(this, Context.ContextClass))
			{
				ViewModelCollection->AddViewModelInstance(Context, ViewModel);
			}
		}
	}
}

void ANHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	InitializeViewModels();
}
