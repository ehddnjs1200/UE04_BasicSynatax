#include "Mag.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AMag::AMag()
{
	MagMesh = CreateDefaultSubobject<UStaticMeshComponent>("MagMesh");
	RootComponent = MagMesh;

	MagMesh->SetSimulatePhysics(true);
	MagMesh->SetEnableGravity(true);
	MagMesh->SetCollisionProfileName(FName(TEXT("PhysicsActor")));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty.SM_AR4_Mag_Empty"));
	if (MeshAsset.Succeeded())
	{
		MagMesh->SetStaticMesh(MeshAsset.Object);
	}


}

void AMag::BeginPlay()
{
	Super::BeginPlay();
	
}


