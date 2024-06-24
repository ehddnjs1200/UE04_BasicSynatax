#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Mag.generated.h"

class UStaticMeshComponent;

UCLASS()
class THIRDPERSONCPP_API AMag : public AActor
{
	GENERATED_BODY()
	
public:	
	AMag();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MagMesh;
};
