#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapon;
class AMag;
class UCCrossHairWidget;
class UCWeaponWidget;
class UStaticMeshComponent;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400.f);

	FORCEINLINE ACWeapon* GetWeapon() override { return Weapon; }
	FORCEINLINE UCWeaponWidget* GetWeaponWidget() { return WeaponWidget; }
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;
	virtual void OnTarget() override;
	virtual void OffTarget() override;

	void ShowMag();
	
	void HiddenMag();

	void Reload();

	void DropMag();

	void ScheduleMeshDestruction();

	void DestroyMagMeshAfterDelay();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void ToggleEquip();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();

	void OnAutoFire();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MagMesh;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin_Zoom();

	UFUNCTION(BlueprintImplementableEvent)
	void End_Zoom();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* CameraComp;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponClass")
	TSubclassOf<ACWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetClass")
	TSubclassOf<UCCrossHairWidget> CrossHairWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetClass")
	TSubclassOf<UCWeaponWidget> WeaponWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "MagClass")
	TSubclassOf<AMag> MagClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapon* Weapon;

	AMag* Mag;
	
	UCCrossHairWidget* CrossHairWidget;
	UCWeaponWidget* WeaponWidget;

	FTimerHandle MeshDestructionTimerHandle;
};
