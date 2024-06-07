// Copyright Epic Games, Inc. All Rights Reserved.


#include "U04_ThirdPersonCPPGameModeBase.h"

AU04_ThirdPersonCPPGameModeBase::AU04_ThirdPersonCPPGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/BP_CPlayer.BP_CPlayer_C'"));

	if (pawnAsset.Succeeded())
	{
		DefaultPawnClass = pawnAsset.Class;
	}
	
	

}