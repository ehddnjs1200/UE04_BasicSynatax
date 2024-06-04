// Fill out your copyright notice in the Description page of Project Settings.


#include "CProperty.h"

// Sets default values
ACProperty::ACProperty()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NumA = 10;
	NumB = 20;
	NumC = 30;
	RealA = 100.1f;
	RealB = 200.2f;
	RealC = 300.3f;
}

// Called when the game starts or when spawned
void ACProperty::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACProperty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

