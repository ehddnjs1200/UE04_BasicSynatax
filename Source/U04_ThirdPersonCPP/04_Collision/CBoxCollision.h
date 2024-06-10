#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoxCollision.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoxCollision();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* TextRenderComp;

};
