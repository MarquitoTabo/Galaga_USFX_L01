// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01Pawn.h"
#include "Galaga_USFX_L01Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Galaga_USFX_L01GameMode.h"
#include "SceneComponentBarrera.h"
#include "Components/SceneComponent.h"
#include "Barrera.h"

const FName AGalaga_USFX_L01Pawn::MoveForwardBinding("MoveForward");
const FName AGalaga_USFX_L01Pawn::MoveRightBinding("MoveRight");
const FName AGalaga_USFX_L01Pawn::FireForwardBinding("FireForward");
const FName AGalaga_USFX_L01Pawn::FireRightBinding("FireRight");

AGalaga_USFX_L01Pawn::AGalaga_USFX_L01Pawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	GunOffset2 = FVector(90.f, 90.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
	Score = 0;

	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla estática
	//SceneComponentBarrera = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SceneComponentBarrera"));

	////Cargar la malla desde un archivo
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BarreraMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe_180.Shape_Pipe_180'"));



	//	SceneComponentBarrera->SetStaticMesh(BarreraMesh.Object);
}
//void AGalaga_USFX_L01Pawn::BeginPlay()
//{
//	Super::BeginPlay();
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CrearBarreraProt, this, &AGalaga_USFX_L01Pawn::CrearBarrera, 15.0f, true);
//	
//	GetWorld()->GetTimerManager().SetTimer(BarreraTimerHandle, this, &AGalaga_USFX_L01Pawn::SpawnBarrera, 15.0f, true);
//}
void AGalaga_USFX_L01Pawn::CrearBarrera()
{
	FVector Location = GetActorLocation() + FVector(100.0f, 0.0f, 0.0f);
	FRotator Rotation = GetActorRotation();

	USceneComponentBarrera* CrearBarrera = GetWorld()->SpawnActor<USceneComponentBarrera>(USceneComponentBarrera::StaticClass(), Location, Rotation);
	if (CrearBarrera != nullptr)
	{
		CrearBarrera->SetWorldLocation(Location);
		CrearBarrera->SetWorldRotation(Rotation);
	}

}


void AGalaga_USFX_L01Pawn::SpawnBarrera()
{
	FVector SpawnLocation = GetActorLocation() + FVector(100.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = GetActorRotation();

	ABarrera* Barrera = GetWorld()->SpawnActor<ABarrera>(ABarrera::StaticClass(), SpawnLocation, SpawnRotation);

	FTimerDelegate TimerDel;

	/*GetWorld()->GetTimerManager().SetTimer(BarreraTimerHandle, Barrera);
		{
			if (Barrera)
			{
				Barrera->Destroy();
			}
		 5.0f, false;
		}*/
	TimerDel.BindLambda([Barrera]()
		{
			if (Barrera)
			{
				Barrera->Destroy();
			}
		});
	//GetWorld()->GetTimerManager().SetTimer(BarreraTimerHandle, TimerDel, 5.0f, false);
}
void AGalaga_USFX_L01Pawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_CrearBarreraProt, this, &AGalaga_USFX_L01Pawn::CrearBarrera, 15.0f, true);

	GetWorld()->GetTimerManager().SetTimer(BarreraTimerHandle, this, &AGalaga_USFX_L01Pawn::SpawnBarrera, 10.0f, true);
}

void AGalaga_USFX_L01Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AGalaga_USFX_L01Pawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	bool masVelocidad = false;

	{
		AGalaga_USFX_L01GameMode* GameMode = Cast<AGalaga_USFX_L01GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			masVelocidad = GameMode->GetPowerUpStatus(500);
		}
	}

	if (masVelocidad)
	{
		MoveSpeed = 2000.0f;
	}

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

void AGalaga_USFX_L01Pawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
			const FVector SpawnLocation2 = GetActorLocation() + FireRotation.RotateVector(GunOffset2);
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AGalaga_USFX_L01Projectile>(SpawnLocation, FireRotation);
			
			}
			bool disparodoble = false;
			{
				AGalaga_USFX_L01GameMode* GameMode = Cast<AGalaga_USFX_L01GameMode>(GetWorld()->GetAuthGameMode());
				if (GameMode != nullptr)
				{
					disparodoble = GameMode->GetPowerUpStatus(200);
				}
			}

			if (disparodoble)
			{

				if (World != nullptr)
				{
					World->SpawnActor<AGalaga_USFX_L01Projectile>(SpawnLocation2, FireRotation);
				}
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AGalaga_USFX_L01Pawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AGalaga_USFX_L01Pawn::ShotTimerExpired()
{
	bCanFire = true;
}

