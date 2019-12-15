// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ATGPlayerController.generated.h"

class AATGAntiTankGun;

/**
 * 
 */
UCLASS()
class AT_GUN_API AATGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	APawn* PreviousPawn;

public:

	/** Function to posses AntiTank Gun and save previous Pawn*/
	void BecomeAntiTankGun(AATGAntiTankGun* AntiTankGun);

	/** Function to retake control of the previous Pawn */
	void PossessPreviousPawn();
};
