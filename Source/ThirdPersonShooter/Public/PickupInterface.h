#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

UINTERFACE()
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class THIRDPERSONSHOOTER_API IPickupInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact|ToInteract")
		void InteractRequest(AActor * OtherActor);
};	