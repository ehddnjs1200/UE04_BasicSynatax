#include "CChest.h"
#include "CPlayer.h"
#include "CKey.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACChest::ACChest()
{

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
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeRotation(FRotator(0, 0, 0));
	TextRenderComp->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	TextRenderComp->TextRenderColor = FColor::Black;
	TextRenderComp->SetText("Press 'F' key to open");
}

void ACChest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UObject* ContentAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Assignment/Chest/MI_Chest.MI_Chest'"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(ContentAsset);

	if (MaterialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
		SkeletalMesh_Head->SetMaterial(0, DynamicMaterial);
		SkeletalMesh_Body->SetMaterial(0, DynamicMaterial);
		DynamicMaterial->SetVectorParameterValue("Emissive", Color);
	}

	OnActorBeginOverlap.AddDynamic(this, &ACChest::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACChest::ActorEndOverlap);

}

void ACChest::BeginPlay()
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

void ACChest::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor!=this)
	{
		if (ACPlayer* Player = Cast<ACPlayer>(OtherActor))
			if (bIsOpen != true)
				Player->Key = Key;
	}
}

void ACChest::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (ACPlayer* Player = Cast<ACPlayer>(OtherActor))
				Player->Key = "";
	}
}

void ACChest::OpenCallback(float val)
{
	if (bIsOpen != true)
	{
		FRotator NewRotation = FRotator::ZeroRotator;
		NewRotation.Pitch = FMath::Lerp(0.0f, 140.0f, val);
		SkeletalMesh_Head->SetRelativeRotation(NewRotation);
	}
}

void ACChest::OnOpenFinished()
{
	bIsOpen = true;
	ChangeText("");
	SpawnKey();
	Inheritedkey->SetKeyMesh(*Keypath,*Key);
}

FString ACChest::DetermineColorName(const FLinearColor& val)
{
	if (val.R > val.G && val.R > val.B)
	{
		Keypath = TEXT("StaticMesh'/Game/Keys/Redkey/RedKey.RedKey'");
		return TEXT("RedKey");
	}
	else if (val.G > val.R && val.G > val.B)
	{
		Keypath = TEXT("StaticMesh'/Game/Keys/GreenKey/GreenKey.GreenKey'");
		return TEXT("GreenKey");
	}
	else if (val.B > val.R && val.B > val.G)
	{
		Keypath = TEXT("StaticMesh'/Game/Keys/BlueKey/BlueKey.BlueKey'");
		return TEXT("BlueKey");
	}
	else
	{
		Keypath = TEXT("");
		return TEXT("Undefined");
	}
}

void ACChest::SpawnKey()
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Inheritedkey = GetWorld()->SpawnActor<ACKey>(SpawnParam);
}

void ACChest::ChangeText(FString Text)
{
	TextRenderComp->SetText(Text);
}
