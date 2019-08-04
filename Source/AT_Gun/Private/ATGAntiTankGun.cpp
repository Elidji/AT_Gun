// Fill out your copyright notice in the Description page of Project Settings.


#include "ATGAntiTankGun.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "ATGAntiTankShell.h"
#include "Public/TimerManager.h"

// Sets default values
AATGAntiTankGun::AATGAntiTankGun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	MeshCompProtection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompProtection"));
	MeshCompProtection->SetupAttachment(CameraComponent);

	MeshCompCanon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompCanon"));
	MeshCompCanon->SetupAttachment(CameraComponent);

	ArrowCanonDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCanonDirection"));
	ArrowCanonDirection->SetupAttachment(MeshCompCanon);

	bCanFire = true;

	ReloadTime = 2.f;
}

// Called when the game starts or when spawned
void AATGAntiTankGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATGAntiTankGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AATGAntiTankGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AATGAntiTankGun::Fire);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

// Fire the gun
void AATGAntiTankGun::Fire()
{
	// Si un projectile a été défini.
	if (ProjectileClass)
	{
		UWorld* World = GetWorld();

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = this;

		FVector SpawnLocation = ArrowCanonDirection->GetComponentLocation();
		FRotator SpawnRotation = ArrowCanonDirection->GetComponentRotation();

		if (World && bCanFire)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Tentative de spawn obus"));
			World->SpawnActor<AATGAntiTankShell>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

			// Une fois que l'obus a été tiré on démarre un timer pour le temps de rechargement.
			World->GetTimerManager().SetTimer(ReloadTimeHandle, this, &AATGAntiTankGun::SetCanFireTrue, ReloadTime);
			bCanFire = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Type de projectile non défini !"));
	}

}

void AATGAntiTankGun::SetCanFireTrue()
{
	bCanFire = true;
}

