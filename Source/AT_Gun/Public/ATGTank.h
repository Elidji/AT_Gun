// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ATGTank.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class AT_GUN_API AATGTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AATGTank();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComponent")
	UStaticMeshComponent* MeshCompChassi;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComponent")
	UStaticMeshComponent* MeshCompTourelle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComponent")
	UStaticMeshComponent* MeshCompCannon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArrowComponent")
	UArrowComponent* ArrowCanonDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
