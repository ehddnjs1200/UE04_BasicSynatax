#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxCollision.h"
#include "CBoxBase_BPEvent.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_BPEvent : public ACBoxCollision
{
	GENERATED_BODY()
	

public:

		virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

		virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;



protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "CPP Custom Evnet")
	void DoSomething();

	UFUNCTION(BlueprintNativeEvent, Category = "CPP Custom Evnet")
	void ResetSomething();
};
