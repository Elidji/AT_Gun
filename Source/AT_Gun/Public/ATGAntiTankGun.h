// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATGAntiTankGun.generated.h"

class UCameraComponent;
class UStaticMeshComponent; 
class UArrowComponent;
class AATGAntiTankShell;

UCLASS()
class AT_GUN_API AATGAntiTankGun : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATGAntiTankGun();

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComponent")
	UStaticMeshComponent* MeshCompProtection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComponent")
	UStaticMeshComponent* MeshCompCanon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArrowComponent")
	UArrowComponent* ArrowCanonDirection;

	/** Son du tir */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	USoundBase* ShotSound;

private:

	bool bCanFire;

	FTimerHandle ReloadTimeHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	float ReloadTime;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AATGAntiTankShell> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Fire the gun
	void Fire();

	void SetCanFireTrue();
	void GetOut();
};
