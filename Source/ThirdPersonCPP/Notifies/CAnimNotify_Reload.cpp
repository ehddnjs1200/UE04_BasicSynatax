#include "CAnimNotify_Reload.h"
#include "CWeaponInterface.h"
#include "CWeapon.h"

void UCAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponInterface* ImplementedOwner = Cast<ICWeaponInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapon* Weapon = ImplementedOwner->GetWeapon();
	if (Weapon == nullptr) return;

	Weapon->SetCurrentAmmo(Weapon->GetMaximumAmmo());
	Weapon->Ammo();
	Weapon->EndReloading();
}
