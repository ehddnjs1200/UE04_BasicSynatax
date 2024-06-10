#include "CBoxCollision.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


ACBoxCollision::ACBoxCollision()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootComp);
	BoxComp->SetWorldScale3D(FVector(3));
	BoxComp->bHiddenInGame = false;

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->TextRenderColor = FColor::Black;
	TextRenderComp->SetText(GetName());

}

void ACBoxCollision::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACBoxCollision::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxCollision::ActorEndOverlap);

}

void ACBoxCollision::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ACBoxCollision::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}



