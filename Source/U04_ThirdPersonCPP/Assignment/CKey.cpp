#include "CKey.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ACKey::ACKey()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComp);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Assignment/Chest/KeyCurve.KeyCurve'"));
	if (Curve.Succeeded())
	{
		MovingCurve = Curve.Object;
	}

	Moving = CreateDefaultSubobject<UTimelineComponent>(TEXT("Moving"));
}

void ACKey::BeginPlay()
{
	Super::BeginPlay();

	Start = GetOwner()->GetActorLocation();

	if (MovingCurve)
	{
		InterpFunction.BindUFunction(this, FName("MovingCallback"));
		MovingFinished.BindUFunction(this, FName("OnMovingFinished"));

		Moving->AddInterpFloat(MovingCurve, InterpFunction);
		Moving->SetTimelineFinishedFunc(MovingFinished);

		Moving->SetLooping(true);
		Moving->SetIgnoreTimeDilation(true);

		Moving->PlayFromStart();
	}
}

void ACKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ACKey::SetKeyMesh(FString Keypath, FString KeyName)
{
	UStaticMesh* KeyMesh = LoadObject<UStaticMesh>(this, *Keypath);
	KEYName = KeyName;
	if (KeyMesh)
	{
		StaticMesh->SetStaticMesh(KeyMesh);
		UE_LOG(LogTemp, Log, TEXT("Mesh loaded and set successfully!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load mesh."));
	}
}

void ACKey::MovingCallback(float val)
{
	FVector NewLocation = FMath::Lerp(Start, Start + FVector(0, 0, 10), val);
	SetActorLocation(NewLocation);
}

void ACKey::OnMovingFinished()
{

}