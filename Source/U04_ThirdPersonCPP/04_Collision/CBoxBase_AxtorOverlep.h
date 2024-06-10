#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxCollision.h"
#include "CBoxBase_AxtorOverlep.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_AxtorOverlep : public ACBoxCollision
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;


private:

	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
};
