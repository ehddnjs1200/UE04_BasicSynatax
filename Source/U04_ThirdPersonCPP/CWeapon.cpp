#include "CWeapon.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	if (meshAsset.Succeeded())
	{
		MeshComp->SetSkeletalMesh(meshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("AnimMontage'/Game/Character/Animations/AR4/Equip_Montage.Equip_Montage'"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> UnEquipMontageAsset(TEXT("AnimMontage'/Game/Character/Animations/AR4/UnEquip_Montage1.UnEquip_Montage1'"));
	if (UnEquipMontageAsset.Succeeded())
	{
		UnEquipMontage = UnEquipMontageAsset.Object;
	}

}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSocket
		);

	}
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACWeapon::Equip()
{
	if (bEquipping == true)return;
	if (bEquipped == true)return;
	bEquipped = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void ACWeapon::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSocket
	);
}

void ACWeapon::End_Equip()
{
	bEquipping = false;
}

void ACWeapon::UnEquip()
{
	if (bEquipping == true)return;
	bEquipped = false;
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

void ACWeapon::Begin_Unequip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSocket
	);
}

void ACWeapon::End_Unequip()
{
	bEquipping = false;
}