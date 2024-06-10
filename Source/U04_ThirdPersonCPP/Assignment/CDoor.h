#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoor.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SkeletalMesh_Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SkeletalMesh_DoorFrame;

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
		void Open();

	UFUNCTION(BlueprintCallable, Category = "CustomEvents")
		void OpenEvents();

public:	
	virtual void Tick(float DeltaTime) override;

};
