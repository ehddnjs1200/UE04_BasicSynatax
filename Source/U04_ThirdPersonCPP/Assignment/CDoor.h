#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CDoor.generated.h"

class UMaterialInstanceDynamic;
class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;


public:

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OpenCallback(float val);

	UFUNCTION()
	void OnOpenFinished();

	FString DetermineColorName(const FLinearColor& val) const;

	void ChangeText(FString Text);


public:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SkeletalMesh_Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SkeletalMesh_DoorFrame;


	UMaterialInstanceDynamic* DynamicMaterial[2];

	UPROPERTY(EditAnywhere)
	FLinearColor Color;

	UPROPERTY()
		UTimelineComponent* Open;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* OpenCurve;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent OpenFinished{};

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComp;

	UPROPERTY(VisibleAnywhere)
	FString Key;

	bool bIsOpen = false;
	bool bIsPossible = false;
};
