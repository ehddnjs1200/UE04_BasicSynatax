#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACChest : public AActor
{
	GENERATED_BODY()
	
public:	
	ACChest();

protected:
	virtual void BeginPlay() override;



public:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SkeletalMesh_Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SkeletalMesh_Body;

	//UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	//void Open();


	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
		void Open();

	UFUNCTION(BlueprintCallable, Category = "CustomEvents")
		void OpenEvents();

public:	
	virtual void Tick(float DeltaTime) override;

};
