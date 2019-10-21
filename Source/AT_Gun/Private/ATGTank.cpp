// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGTank.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"
#include "Engine/EngineTypes.h"
#include "Components/PrimitiveComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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

	MeshCompTourelle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompTourelle"));
	MeshCompTourelle->SetupAttachment(BoxCompTourelle);

	CapsCompCannon = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsCompCannon"));
	CapsCompCannon->SetupAttachment(BoxCompTourelle);

	MeshCompCannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompCanon"));
	MeshCompCannon->SetupAttachment(CapsCompCannon);

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(CapsCompCannon);

	VieChassi = 0.f;
	VieTourelle = 0.f;
	VieCannon = 0.f;

	bPatrol = false;
}

// Called when the game starts or when spawned
void AATGTank::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
	
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

/// This is the actor damage handler.   
float AATGTank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
    const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		// Récupération des info du hit
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)& DamageEvent;
		FHitResult HitResult = PointDamageEvent->HitInfo;

		// Récupération du component touché
		UPrimitiveComponent* ComponentHit = HitResult.GetComponent();

		if (ComponentHit == BoxCompChassi)
		{
			if (ActualDamage > 0.f)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Chassi touche"));
				VieChassi -= ActualDamage;
			}
			// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
			if (VieChassi <= 0.f)
			{
				SetLifeSpan(0.001f);
			}
		}
		else if (ComponentHit == BoxCompTourelle)
		{
			if (ActualDamage > 0.f)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Tourelle touche"));
				VieTourelle -= ActualDamage;
			}
			// If the damage depletes our health set our lifespan to zero - which will destroy the component  
			if (VieTourelle <= 0.f)
			{
				MeshCompTourelle->DestroyComponent(false);
				BoxCompTourelle->DestroyComponent(false);
				MeshCompCannon->DestroyComponent(false);
				CapsCompCannon->DestroyComponent(false);
			}

		}
		else if (ComponentHit == CapsCompCannon)
		{
			if (ActualDamage > 0.f)
			{
				VieCannon -= ActualDamage;
			}
			if (VieCannon <= 0.f)
			{
				MeshCompCannon->DestroyComponent(false);
				CapsCompCannon->DestroyComponent(false);
			}
		}
	}

	return ActualDamage;
}

void AATGTank::MoveToNextPatrolPoint()
{
		// Assign next patrol point.
		if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
		{
			CurrentPatrolPoint = FirstPatrolPoint;
		}
		else
		{
			CurrentPatrolPoint = SecondPatrolPoint;
		}

		//UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrolPoint);
}
