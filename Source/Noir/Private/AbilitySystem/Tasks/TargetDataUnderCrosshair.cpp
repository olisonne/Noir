// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/TargetDataUnderCrosshair.h"

#include "Kismet/GameplayStatics.h"

UTargetDataUnderCrosshair* UTargetDataUnderCrosshair::CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCrosshair* MyObj = NewAbilityTask<UTargetDataUnderCrosshair>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderCrosshair::Activate()
{
    FVector2D ViewportSize;
    if (GEngine && GEngine->GameViewport)
    {
        GEngine->GameViewport->GetViewportSize(ViewportSize);
    }

    FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
    FVector CrosshairWorldPosition;
    FVector CrosshairWorldDirection;

    bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
        UGameplayStatics::GetPlayerController(this, 0),
        CrosshairLocation,
        CrosshairWorldPosition,
        CrosshairWorldDirection);

	FHitResult TraceHitResult;
	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		FVector End = Start + CrosshairWorldDirection * TraceDistance;

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			TraceHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility
		);
		if (!TraceHitResult.bBlockingHit)
		{
			TraceHitResult.ImpactPoint = End;
		}

		ValidData.Broadcast(TraceHitResult.ImpactPoint);

	}
}
