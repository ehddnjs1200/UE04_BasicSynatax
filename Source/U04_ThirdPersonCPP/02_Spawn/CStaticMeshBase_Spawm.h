// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshBase_Spawm.generated.h"

class ACStaticMeshBase;

UCLASS()
class U04_THIRDPERSONCPP_API ACStaticMeshBase_Spawm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACStaticMeshBase_Spawm();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		UClass* WhatIsClassRef;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ACStaticMeshBase> WhatIsTSubClassOf;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
		TSubclassOf<ACStaticMeshBase> SpawnClasses[4];

private:
	ACStaticMeshBase* SpawnedObjects[4];

};
