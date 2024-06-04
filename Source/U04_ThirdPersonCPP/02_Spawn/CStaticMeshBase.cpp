

#include "CStaticMeshBase.h"

ACStaticMeshBase::ACStaticMeshBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh>meshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	if (meshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(meshAsset.Object);
	}

}

void ACStaticMeshBase::BeginPlay()
{
	Super::BeginPlay();
	
}


