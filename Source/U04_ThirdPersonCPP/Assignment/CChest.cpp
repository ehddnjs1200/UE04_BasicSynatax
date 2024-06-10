#include "CChest.h"
#include "Components/StaticMeshComponent.h"

ACChest::ACChest()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	SkeletalMesh_Head = CreateDefaultSubobject<UStaticMeshComponent>("SkeletalMesh_Head");
	SkeletalMesh_Head->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> HeadAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestTop.SM_ChestTop'"));
	SkeletalMesh_Head->SetStaticMesh(HeadAsset.Object);

	SkeletalMesh_Body = CreateDefaultSubobject<UStaticMeshComponent>("SkeletalMesh_Body");
	SkeletalMesh_Body->SetupAttachment(RootComp);
	ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAsset(TEXT("StaticMesh'/Game/Assignment/Chest/SM_ChestBottom.SM_ChestBottom'"));
	SkeletalMesh_Body->SetStaticMesh(BodyAsset.Object);


}

void ACChest::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACChest::OpenEvents()
{
	Open();
}


void ACChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

