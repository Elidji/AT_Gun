// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGTank.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AATGTank::AATGTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshCompChassi = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompChassi"));
	RootComponent = MeshCompChassi;

	BoxCompChassi = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompChassi"));
	BoxCompChassi->SetupAttachment(MeshCompChassi);
	BoxCompChassi->OnComponentHit.AddDynamic(this, &AATGTank::OnHitChassi);

	MeshCompTourelle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompTourelle"));
	MeshCompTourelle->SetupAttachment(MeshCompChassi);

	BoxCompTourelle = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompTourelle"));
	BoxCompTourelle->SetupAttachment(MeshCompTourelle);
	BoxCompTourelle->OnComponentHit.AddDynamic(this, &AATGTank::OnHitTourelle);

	MeshCompCannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompCanon"));
	MeshCompCannon->SetupAttachment(MeshCompTourelle);

	CapsCompCannon = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsCompCannon"));
	CapsCompCannon->SetupAttachment(MeshCompCannon);
	CapsCompCannon->OnComponentHit.AddDynamic(this, &AATGTank::OnHitCannon);

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(MeshCompCannon);

	VieChassi = 0.f;
	VieTourelle = 0.f;
	VieCannon = 0.f;
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

// Appellé quand le chassi est touché
void AATGTank::OnHitChassi(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Chassi touche"));
}

// Appellé quand la tourelle est touchée
void AATGTank::OnHitTourelle(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Tourelle touchee"));
}

// Appellé quand le cannon est touché
void AATGTank::OnHitCannon(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Cannon touche"));
}
