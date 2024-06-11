#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CChest.generated.h"

class UMaterialInstanceDynamic;
class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACChest : public AActor
{
	GENERATED_BODY()
	
public:	
	ACChest();

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

	FString DetermineColorName(const FLinearColor& Color) const;

public:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SkeletalMesh_Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SkeletalMesh_Body;


	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere)
		FLinearColor Color = FLinearColor(0, 0, 0, 0);


	UPROPERTY()
	UTimelineComponent* Open;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* OpenCurve;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent OpenFinished{};

	UPROPERTY(VisibleAnywhere)
	FString Key;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* TextRenderComp;

	bool bIsOpen = false;
};
