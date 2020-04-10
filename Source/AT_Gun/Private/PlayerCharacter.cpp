// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "ATGAntiTankGun.h"
#include "ATGPlayerController.h"
#include "ATGWeapon.h"
#include "DrawDebugHelpers.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	PlayerMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh1P"));
	PlayerMesh1P->SetOnlyOwnerSee(true);				// Set so only owner can see mesh
	PlayerMesh1P->SetupAttachment(CameraComponent);	// Attach mesh to FirstPersonCameraComponent
	PlayerMesh1P->bCastDynamicShadow = false;			// Disallow mesh to cast dynamic shadows
	PlayerMesh1P->CastShadow = false;				// Disallow mesh to cast other shadows

	// Create a gun mesh component
// 	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
// 	FP_Gun->SetOnlyOwnerSee(true);			// Only the owning player will see this mesh
// 	FP_Gun->bCastDynamicShadow = false;		// Disallow mesh to cast dynamic shadows
// 	FP_Gun->CastShadow = false;			// Disallow mesh to cast other shadows
// 	FP_Gun->SetupAttachment(PlayerMesh1P, TEXT("GripPoint"));

	InteractionDistance = 200.f;
	bTraceDebugLine = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	NewLocation = PlayerMesh1P->GetSocketLocation("GripPoint");

	FActorSpawnParameters SpawnInfo;
	AATGWeapon* Weapon = GetWorld()->SpawnActor<AATGWeapon>(ToSpawn, FVector(0.f,0.f,0.f), FRotator::ZeroRotator);

	Weapon->AttachToComponent(PlayerMesh1P, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("GripPoint")));
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to inputs
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::Interact()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	FVector InteractionEnd;
	FHitResult HitResult;

	GetController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	// Calcul du point de fin pour l'intéraction
	InteractionEnd = PlayerLocation + PlayerRotation.Vector() * InteractionDistance;

	HitResult = Trace(PlayerLocation, InteractionEnd);
	if (HitResult.bBlockingHit)
	{
		// Si la trace a touché quelquechose on vérifie si il s'agit d'un antitank gun
		AATGAntiTankGun* AntiTankGun = Cast<AATGAntiTankGun>(HitResult.GetActor());
		if (AntiTankGun)
		{
			// Si c'est un antitank gun alors on en prend le controlle après avoir vérifier si le playercontroller est le bon
			AATGPlayerController* PlayerController = Cast<AATGPlayerController>(GetController());
			if (PlayerController)
			{
				PlayerController->BecomeAntiTankGun(AntiTankGun);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Mauvais PlayerController défini !"));
			}
		}
	}
}

FHitResult APlayerCharacter::Trace(const FVector& StartTrace, const FVector& EndTrace) const
{
	// Perform trace to retrieve hit info
	//FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(WeaponTrace), true, Instigator);
	//TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility);


	// Traçage de la ligne de debug si actif
	if (bTraceDebugLine)
	{
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 2.0f, '\000', 7.f);

		if (bHit)
		{
			DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5), FColor::Orange, false, 2.f);
		}
	}

	return Hit;
}