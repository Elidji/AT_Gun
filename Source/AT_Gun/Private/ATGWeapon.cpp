// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGWeapon.h"

// Sets default values
AATGWeapon::AATGWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

}

// Called when the game starts or when spawned
void AATGWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATGWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

