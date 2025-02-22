// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGAntiTankShell.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ATGTank.h"
#include "GameFramework/DamageType.h"

// Sets default values
AATGAntiTankShell::AATGAntiTankShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AATGAntiTankShell::OnHit);	// set up a notification for when this component hits something blocking
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	//MeshComp->SetSimulatePhysics(true);
	MeshComp->SetupAttachment(GetRootComponent());

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AATGAntiTankShell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATGAntiTankShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATGAntiTankShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tentative Creation impulse"));

	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			AATGTank* Tank = Cast<AATGTank>(OtherActor);
			if (Tank)
			{
				TSubclassOf<UDamageType> const DamageTypeShell = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				const float DamageAmount = 60.0f;
				FVector HitOrientation = GetActorForwardVector();
				FPointDamageEvent DamageEvent(DamageAmount, Hit, HitOrientation, DamageTypeShell);

				Tank->TakeDamage(DamageAmount, DamageEvent, PlayerController, this);
			}
		}
		
		// A l'impact jouer une explosion avec le son
	
		ExplosionTransform.SetLocation(Hit.ImpactPoint);
		UWorld* World = GetWorld();
		if (World && ExplosionParticule && ExplosionSound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawn explosion"));
			// Effet de particule
			UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionParticule, ExplosionTransform, false);

			// Son
			UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, ExplosionTransform.GetLocation());
		}
		UE_LOG(LogTemp, Warning, TEXT("apres spawn explosion"));

		Destroy();
	}
}

