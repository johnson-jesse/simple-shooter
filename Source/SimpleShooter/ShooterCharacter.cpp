// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Gun = nullptr;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	// No gun bone is on the mesh I chose for this tutorial since the requested one crashes UE5
	// GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(
		TEXT("MoveForward"),
		this,
		&AShooterCharacter::MoveForward);

	PlayerInputComponent->BindAxis(
		TEXT("MoveRight"),
		this,
		&AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis(
		TEXT("LookUp"),
		this,
		&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis(
		TEXT("LookRight"),
		this,
		&APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(
		TEXT("LookUpRate"),
		this,
		&AShooterCharacter::LookUpRate);

	PlayerInputComponent->BindAxis(
		TEXT("LookRightRate"),
		this,
		&AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction(
		TEXT("Jump"),
		IE_Pressed,
		this,
		&ACharacter::Jump);

	PlayerInputComponent->BindAction(
		TEXT("Shoot"),
		IE_Pressed,
		this,
		&AShooterCharacter::Shoot);
}

void AShooterCharacter::MoveForward(const float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(const float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(const float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(const float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}