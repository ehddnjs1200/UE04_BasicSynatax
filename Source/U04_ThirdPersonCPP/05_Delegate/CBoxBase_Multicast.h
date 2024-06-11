#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxCollision.h"
#include "CBoxBase_Multicast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastBegimOverlap,int32,FLinearColor);


UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Multicast : public ACBoxCollision
{
	GENERATED_BODY()
	
protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;


public:
	FMulticastBegimOverlap OnMulticastBeginOverlap;

};
