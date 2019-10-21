// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ATGTank.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class UCapsuleComponent;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CollisionShape")
	UBoxComponent* BoxCompChassi;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CollisionShape")
	UBoxComponent* BoxCompTourelle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CollisionShape")
	UCapsuleComponent* CapsCompCannon;

	UPROPERTY(EditDefaultsOnly, Category = "Vie")
	float VieChassi;

	UPROPERTY(EditDefaultsOnly, Category = "Vie")
	float VieTourelle;

	UPROPERTY(EditDefaultsOnly, Category = "Vie")
	float VieCannon;

	/* Let the guard go on patrol */
	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bPatrol;

	/* First of two patrol points to patrol between */
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* FirstPatrolPoint;

	/* Second of two patrol points to patrol between */
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
	AActor* SecondPatrolPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The current point the actor is either moving to or standing at
	AActor* CurrentPatrolPoint;

	FRotator OriginalRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	void MoveToNextPatrolPoint();

};
