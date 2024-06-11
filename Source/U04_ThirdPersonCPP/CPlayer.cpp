#include "CPlayer.h"
#include "Assignment/CChest.h"
#include "Assignment/CDoor.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "CAnimInstance.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 100));
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	ConstructorHelpers::FClassFinder<UCAnimInstance> AnimInstanceClass(TEXT("/Game/ABP_CPlayer"));

	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACPlayer::ActorEndOverlap);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);


	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Open", EInputEvent::IE_Pressed, this, &ACPlayer::HandleFKeyPressed);

}

void ACPlayer::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		Thing = OtherActor;
	}
}

void ACPlayer::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Thing = nullptr;
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::HandleFKeyPressed()
{
	
	if (Thing != nullptr)
	{
		if (ACChest* Chest = Cast<ACChest>(Thing))
			OpenChest(Chest);
		
		if (ACDoor* Door = Cast<ACDoor>(Thing))
			OpenDoor(Door);
	}
}

void ACPlayer::OpenDoor(ACDoor* Door)
{
	if (Door->bIsPossible)
	{
		Door->Open->PlayFromStart();
	}
	else
	{
		FString Text = "You don't have " + Key + ".";
		Door->ChangeText(Text);
	}
	for (int32 i = 0; i < PossessKeys.Num(); i++)
	{
		if (PossessKeys[i] == Key)
		{
			PossessKeys.RemoveAt(i);
			break;
		}
	}
}

void ACPlayer::OpenChest(ACChest* Chest)
{
	if (!Chest->bIsOpen)
	{
		Chest->Open->PlayFromStart();
	}
	for (int32 i = 0; i < PossessKeys.Num(); i++)
	{
		if (PossessKeys[i] == Key)
		{
			bIsSame = true;
			break;
		}
	}
	if (!bIsSame)
	{
		PossessKeys.Add(Key);
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CLog::Print("PossessKeys", 100);

	if (PossessKeys.Num() != 0)
	{
		for (int32 i = 0; i < PossessKeys.Num(); i++)
		{
			CLog::Print(PossessKeys[i], 99 - i, 0.1f);
		}
	}
}



