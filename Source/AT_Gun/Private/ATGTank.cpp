// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGTank.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AATGTank::AATGTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshCompChassi = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompChassi"));
	RootComponent = MeshCompChassi;

	MeshCompTourelle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompTourelle"));
	MeshCompTourelle->SetupAttachment(MeshCompTourelle);

	MeshCompCannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompCanon"));
	MeshCompCannon->SetupAttachment(GetRootComponent());

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(MeshCompCannon);
}

// Called when the game starts or when spawned
void AATGTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATGTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AATGTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

