#include "CAnimNotifyState_DropMag.h"
#include "CWeaponInterface.h"
#include "CPlayer.h"


FString UCAnimNotifyState_DropMag::GetNotifyName_Implementation() const
{
	return "DropMag";
}

void UCAnimNotifyState_DropMag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	Player->DropMag();
}

void UCAnimNotifyState_DropMag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	
}