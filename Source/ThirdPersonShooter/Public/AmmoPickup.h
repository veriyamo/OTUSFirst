// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AAmmoPickup : public APickup
{
	GENERATED_BODY()



protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
		int32 GetAmmoAmount();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 AmmoAmount = 30;


};
