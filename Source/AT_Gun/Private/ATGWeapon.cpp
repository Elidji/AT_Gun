// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGWeapon.h"
#include "Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "ATGAntiTankShell.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AATGWeapon::AATGWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
 
	// Create a mesh component
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(WeaponMesh);

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

// Fire the gun
void AATGWeapon::Fire()
{
	// Si un projectile a été défini.
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		/*ActorSpawnParams.Instigator = this;*/

		FVector SpawnLocation = ArrowCanonDirection->GetComponentLocation();
		FRotator SpawnRotation = ArrowCanonDirection->GetComponentRotation();
		FVector Location = GetActorLocation();

		if (World && bCanFire)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Tentative de spawn obus"));
			World->SpawnActor<AATGAntiTankShell>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			// Son du tir
			if (FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, FireSound, Location);
			}

			// Une fois que l'obus a été tiré on démarre un timer pour le temps de rechargement.
			World->GetTimerManager().SetTimer(ReloadTimeHandle, this, &AATGWeapon::SetCanFireTrue, ReloadTime);
			bCanFire = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Type de projectile non défini !"));
	}

}

void AATGWeapon::SetCanFireTrue()
{
	bCanFire = true;
}

