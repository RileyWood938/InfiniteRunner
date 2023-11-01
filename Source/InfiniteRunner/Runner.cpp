// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);  // Attach the spring arm to the root component
	SpringArmComponent->TargetArmLength = 1000;

	// Create and attach the camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);  // Attach the camera to the spring arm

}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	/*InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), Priority);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction("Jump", ETriggerEvent::Triggered, this, &ARunner::StartJump);*/

	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunner::StartJump);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARunner::MoveRight);
	PlayerInputComponent->BindAxis("MoxeLeft", this, &ARunner::MoveLeft);*/
}

void ARunner::MoveRight(float value) {
	if (value != 0.0f)
	{

		AddMovementInput(FVector(0, 1, 0), value);
	}
}

void ARunner::MoveLeft(float value) {
	if (value != 0.0f)
	{

		AddMovementInput(FVector(0, -1, 0), value);
	}
}

void ARunner::StartJump() {
	Jump();
}