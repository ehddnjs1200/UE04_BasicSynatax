#include "CAnimNotifyState_EquipMag.h"
#include "CWeaponInterface.h"
#include "CPlayer.h"

FString UCAnimNotifyState_EquipMag::GetNotifyName_Implementation() const
{
	return "EquipMag";
}

void UCAnimNotifyState_EquipMag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	Player->ShowMag();
}

void UCAnimNotifyState_EquipMag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	Player->HiddenMag();
}
