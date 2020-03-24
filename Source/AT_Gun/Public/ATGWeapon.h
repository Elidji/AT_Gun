// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATGWeapon.generated.h"

class AATGAntiTankShell;
class UArrowComponent;

UCLASS()
class AT_GUN_API AATGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATGWeapon();

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	/** Effet du tir */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particules")
	UParticleSystem* MuzzleFlash;

	/** Son du tir */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sons")
	USoundBase* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArrowComponent")
	UArrowComponent* ArrowCanonDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AATGAntiTankShell> ProjectileClass;

	bool bCanFire;

	FTimerHandle ReloadTimeHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	float ReloadTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void SetCanFireTrue();

};
