// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshBase_Spawm.h"
#include "CStaticMeshBase.h"

// Sets default values
ACStaticMeshBase_Spawm::ACStaticMeshBase_Spawm()
{

}

// Called when the game starts or when spawned
void ACStaticMeshBase_Spawm::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < 4; i++)
	{
		FTransform trasnform;

		SpawnedObjects[i] = GetWorld()->SpawnActor<ACStaticMeshBase>(SpawnClasses[i], trasnform);

		FVector location = GetActorLocation();

		SpawnedObjects[i]->SetActorLocation(FVector(location.X, location.Y + i * 200, location.Z));
	};


}

