#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CKey.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ACKey();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetKeyMesh(FString Keypath, FString KeyName);

public:
	UFUNCTION()
	void MovingCallback(float val);

	UFUNCTION()
	void OnMovingFinished();


public:
	UPROPERTY()
	UTimelineComponent* Moving;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MovingCurve;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent MovingFinished{};


	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	FString KEYName;

	FVector Start;

};
