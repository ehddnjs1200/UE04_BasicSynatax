

#include "CStaticMeshBase.h"

ACStaticMeshBase::ACStaticMeshBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);
}

void ACStaticMeshBase::BeginPlay()
{
	Super::BeginPlay();
	
}


