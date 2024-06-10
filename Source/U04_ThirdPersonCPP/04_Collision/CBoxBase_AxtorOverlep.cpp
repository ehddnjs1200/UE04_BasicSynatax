#include "CBoxBase_AxtorOverlep.h"
#include "Global.h"

void ACBoxBase_AxtorOverlep::BeginPlay()
{
	Super::BeginPlay();

}

void ACBoxBase_AxtorOverlep::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	CLog::Print("OtherActor : " + OtherActor->GetActorLabel());
}
