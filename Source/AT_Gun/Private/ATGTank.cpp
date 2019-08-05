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

	BoxCompChassi = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompChassi"));
	RootComponent = BoxCompChassi;

	MeshCompChassi = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompChassi"));
	MeshCompChassi->SetupAttachment(BoxCompChassi);

	BoxCompTourelle = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompTourelle"));
	BoxCompTourelle->SetupAttachment(BoxCompChassi);
	BoxCompTourelle->OnComponentHit.AddDynamic(this, &AATGTank::OnHitTourelle);

	MeshCompTourelle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompTourelle"));
	MeshCompTourelle->SetupAttachment(BoxCompTourelle);

	CapsCompCannon = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsCompCannon"));
	CapsCompCannon->SetupAttachment(BoxCompTourelle);
	CapsCompCannon->OnComponentHit.AddDynamic(this, &AATGTank::OnHitCannon);

	MeshCompCannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompCanon"));
	MeshCompCannon->SetupAttachment(CapsCompCannon);

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(CapsCompCannon);

	VieChassi = 0.f;
	VieTourelle = 0.f;
	VieCannon = 0.f;
}

// Called when the game starts or when spawned
void AATGTank::BeginPlay()
{
	Super::BeginPlay();

	BoxCompChassi->OnComponentHit.AddDynamic(this, &AATGTank::OnHitChassi);
	
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
