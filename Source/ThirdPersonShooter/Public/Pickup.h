#pragma once

#include "CoreMinimal.h"
#include "PickupInterface.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:
	// Устанавливает значения по умолчанию для свойств этого объекта actor
	APickup();

	// Вызывается каждый кадр
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* PickupMesh;

protected:
	// Вызывается при запуске игры или при возрождении
	virtual void BeginPlay() override;
	
	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
		float BaseTurnRate = 45.f;

private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere)
		class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere)
		class UNiagaraComponent* PickupEffectComponent;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* PickupEffect;

	FTimerHandle BindOverlapTimer;
	float BindOverlapTime = 0.25f;
	void BindOverlapTimerFinished();
};