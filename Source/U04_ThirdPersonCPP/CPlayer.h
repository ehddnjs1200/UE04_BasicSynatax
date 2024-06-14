#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapon;
class UCUserWidget;


UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter , public ICWeaponInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400.f);

	FORCEINLINE ACWeapon* GetWeapon() override { return Weapon; }


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

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);


protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin_Zoom();

	UFUNCTION(BlueprintImplementableEvent)
	void End_Zoom();


private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* CameraComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponClass")
	TSubclassOf<ACWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "CUserWidget")
	TSubclassOf<UCUserWidget> CUserWidget;

	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapon* Weapon;
	UCUserWidget* UserWidget;
};
