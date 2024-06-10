#include "CDoor.h"
#include "Components/StaticMeshComponent.h"

ACDoor::ACDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	SkeletalMesh_Door = CreateDefaultSubobject<UStaticMeshComponent>("SkeletalMesh_Door");
	SkeletalMesh_Door->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> HeadAsset(TEXT("StaticMesh'/Game/Assignment/Door/Props/SM_Door.SM_Door'"));
	SkeletalMesh_Door->SetStaticMesh(HeadAsset.Object);
	SkeletalMesh_Door->SetRelativeLocation(FVector(0, 44, 0));

	SkeletalMesh_DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("SkeletalMesh_DoorFrame");
	SkeletalMesh_DoorFrame->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAsset(TEXT("StaticMesh'/Game/Assignment/Door/Props/SM_DoorFrame.SM_DoorFrame'"));
	SkeletalMesh_DoorFrame->SetStaticMesh(BodyAsset.Object);

}

void ACDoor::BeginPlay()
{
	Super::BeginPlay();
	
}



void ACDoor::OpenEvents()
{
	Open();
}


void ACDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

