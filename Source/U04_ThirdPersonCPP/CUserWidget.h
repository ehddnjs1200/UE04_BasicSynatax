// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class U04_THIRDPERSONCPP_API UCUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTarget();
	UFUNCTION(BlueprintImplementableEvent)
	void OffTarget();

};