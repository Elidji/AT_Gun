// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGPlayerController.h"
#include "ATGAntiTankGun.h"

void AATGPlayerController::BecomeAntiTankGun(AATGAntiTankGun* AntiTankGun)
{
	// Sauvegarde du pawn précédent pour pouvoir en reprendre le controle plus tard
	PreviousPawn = GetPawn();
	Possess(AntiTankGun);
}

void AATGPlayerController::PossessPreviousPawn()
{
	if (PreviousPawn)
	{
		Possess(PreviousPawn);
	}
}
