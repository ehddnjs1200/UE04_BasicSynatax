#include "CDoor.h"
#include "CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


ACDoor::ACDoor()
{
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

	Open = CreateDefaultSubobject<UTimelineComponent>(TEXT("Open"));

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Assignment/Chest/OpenCurve.OpenCurve'"));
	if (Curve.Succeeded())
	{
		OpenCurve = Curve.Object;
	}

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootComp);
	BoxComp->SetWorldScale3D(FVector(3));
	BoxComp->bHiddenInGame = false;

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootComp);
	TextRenderComp->SetRelativeLocation(FVector(-42, 0, 185.0));
	TextRenderComp->SetRelativeRotation(FRotator(180, 180, 0));
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->TextRenderColor = FColor::Black;
	TextRenderComp->SetText("Press 'F' key to open");
}

void ACDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UObject* ContentAsset1 = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Door/Materials/MI_Door.MI_Door'"));
	UObject* ContentAsset2 = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Door/Materials/MI_Frame.MI_Frame'"));
	UMaterialInstanceConstant* MaterialAsset1 = Cast<UMaterialInstanceConstant>(ContentAsset1);
	UMaterialInstanceConstant* MaterialAsset2 = Cast<UMaterialInstanceConstant>(ContentAsset2);

	if (MaterialAsset1&& MaterialAsset2)
	{
		DynamicMaterial[0] = UMaterialInstanceDynamic::Create(MaterialAsset1, nullptr);
		DynamicMaterial[1] = UMaterialInstanceDynamic::Create(MaterialAsset2, nullptr);
		SkeletalMesh_Door->SetMaterial(0, DynamicMaterial[0]);
		SkeletalMesh_DoorFrame->SetMaterial(0, DynamicMaterial[1]);
		DynamicMaterial[0]->SetVectorParameterValue("Color", Color);
		DynamicMaterial[1]->SetVectorParameterValue("Color", Color);
	}

	OnActorBeginOverlap.AddDynamic(this, &ACDoor::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDoor::ActorEndOverlap);

}

void ACDoor::BeginPlay()
{
	Super::BeginPlay();

	if (OpenCurve)
	{
		InterpFunction.BindUFunction(this, FName("OpenCallback"));
		OpenFinished.BindUFunction(this, FName("OnOpenFinished"));

		Open->AddInterpFloat(OpenCurve, InterpFunction);
		Open->SetTimelineFinishedFunc(OpenFinished);

		Open->SetLooping(false);
		Open->SetIgnoreTimeDilation(true);
	}
	Key = DetermineColorName(Color);
}

void ACDoor::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		ACPlayer* Player = Cast<ACPlayer>(OtherActor);
		Player->Key = Key;
		for (int32 i = 0; i < Player->PossessKeys.Num(); i++)
		{
			if (Player->PossessKeys[i] == Key)
			{
				bIsPossible = true;	
			}
		}
	}
}

void ACDoor::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	bIsPossible = false;
	Player->Key = "";
}

void ACDoor::OpenCallback(float val)
{
	if (bIsOpen != true)
	{
		FRotator NewRotation = FRotator::ZeroRotator;
		NewRotation.Yaw = FMath::Lerp(0.0f, -120.0f, val);
		SkeletalMesh_Door->SetRelativeRotation(NewRotation);
	}
}

void ACDoor::OnOpenFinished()
{
	bIsOpen = true;
	ChangeText("");
}

FString ACDoor::DetermineColorName(const FLinearColor& val) const
{
	if (val.R > val.G && val.R > val.B)
	{
		return TEXT("RedKey");
	}
	else if (val.G > val.R && val.G > val.B)
	{
		return TEXT("GreenKey");
	}
	else if (val.B > val.R && val.B > val.G)
	{
		return TEXT("BlueKey");
	}
	else
	{
		return TEXT("Undefined");
	}
}

void ACDoor::ChangeText(FString Text)
{
	TextRenderComp->SetText(Text);
}


