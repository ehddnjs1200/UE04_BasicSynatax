#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACDoor;
class ACChest;
class ACKey;

UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:

	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void HandleFKeyPressed();

	void OpenDoor(ACDoor* Door);

	void OpenChest(ACChest* Chest);

	virtual void Tick(float DeltaTime) override;



public:

	void PickUpKey(ACChest* Chest);

	void FindKey(ACDoor* Door);

	void UseKey(ACDoor* Door);

	void RemoveKey(ACKey* KeyName);

	void CountKey(FString Text, bool Increase);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

public:

	FString Key = "None";


	TArray<ACKey*> PossessKeys;

	AActor* FindKeys;

	AActor* Thing;

	bool bIsSame = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Red = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Green = 0;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 Blue = 0;

};
