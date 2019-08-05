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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnHitChassi(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnHitTourelle(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnHitCannon(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
