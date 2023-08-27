// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

void AHealthPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, FromSweep, SweepResult);

	if (OtherActor->Implements<UPickupInterface>())
	{
		IPickupInterface::Execute_InteractRequest(OtherActor, this);
	}
	Destroy();
}
