// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameManager.h"

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

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunner::BeginOverlap);
}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController()); //Get the controller for the player
	if (PlayerController) {//make sure the cast is successful
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()); //turn it into a Enhanced Input Subsystem
		if (Subsystem) { //again check for cast success
			Subsystem->AddMappingContext(InputMapping, 0); //add a mapping context which is exposed to the editor
		}
	}
}

// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(FVector(0, 1, 0), 1.0);
}


void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) { //Cast PlayerInputComponent to Enhanced Version
		enhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ARunner::Test); //binds ARunner::Move to the MoveAction UInputAction
		enhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARunner::Move); //binds ARunner::Move to the MoveAction UInputAction
		enhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARunner::Look); //binds ARunner::Move to the MoveAction UInputAction

	}
}

void ARunner::Test(const FInputActionValue& Value) {
	const bool currentValue = Value.Get<bool>();
	if (currentValue) {
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("hit")));
		Jump();

	}
}

void ARunner::Move(const FInputActionValue& Value) {
	const FVector2D movementVector = Value.Get<FInputActionValue::Axis2D>();
	/*const FVector forward = GetActorForwardVector();
	AddMovementInput(forward, movementVector.Y);
	const FVector right = GetActorRightVector();
	AddMovementInput(right, movementVector.X);*/


	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, movementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, movementVector.X);

}

void ARunner::Look(const FInputActionValue& Value)
{
	const FVector2D lookAxisValue = Value.Get<FVector2D>();
	if (GetController()) {
		AddControllerYawInput(lookAxisValue.X);
		AddControllerPitchInput(lookAxisValue.Y);
	}
}

void ARunner::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Runner Hit Object"));
	if (manager) {
		manager->SpawnGround();
	}
}