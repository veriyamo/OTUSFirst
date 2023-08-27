#include "Pickup.h"
#include "Sound/SoundCue.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>

#define CUSTOM_DEPTH_PURPLE 250

// Устанавливает значения по умолчанию
APickup::APickup()
{
	// Настройте этот объект actor на вызов Tick() для каждого кадра. Вы можете отключить эту функцию, чтобы повысить производительность, если она вам не нужна.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(100.f);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapSphere->AddLocalOffset(FVector(0.f, 0.f, 50.f));

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(OverlapSphere);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
	PickupMesh->SetRenderCustomDepth(true);
	PickupMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_PURPLE);

	PickupEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
	PickupEffectComponent->SetupAttachment(RootComponent); 
}

// Вызывается при запуске игры или при возрождении
void APickup::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(BindOverlapTimer, this, &APickup::BindOverlapTimerFinished, BindOverlapTime);
}

void APickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
}

void APickup::BindOverlapTimerFinished()
{
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnSphereOverlap);
}
// Вызывается каждый кадр
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PickupMesh->AddWorldRotation(FRotator(0.f, BaseTurnRate * DeltaTime, 0.f));
}

void APickup::Destroyed()
{
	Super::Destroyed();
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, PickupEffect, GetActorLocation(), GetActorRotation());
	}
}