// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "GroundSpawner.h"
#include "ObstacleSpawner.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	GroundSpawner = GetWorld()->SpawnActor<AGroundSpawner>();
	ObstacleSpawner = GetWorld()->SpawnActor<AObstacleSpawner>();

	for (int i = 0; i < 10; i++) {
		SpawnGround();
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager::SpawnGround() {
	FVector location = FVector(0, 1000 * groundTilesSpawned, 0);
	AActor* groundTile = nullptr;
	if (GroundSpawner)
	{
		groundTile = GroundSpawner->Spawn(this, location);
		groundTilesSpawned++;
		if (ObstacleSpawner) {
			if (groundTile) {
				TArray<UActorComponent*> GroundComponents;
				GroundComponents = groundTile->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "ground");

				if (GroundComponents.Num() > 0)
				{
					UActorComponent* GroundComponent = GroundComponents[0];
					USceneComponent* GroundSceneComponent = Cast<USceneComponent>(GroundComponent);
					FTransform ComponentTransform = GroundSceneComponent->GetComponentTransform();
					FVector Scale = ComponentTransform.GetScale3D();
					float randomXLocation = FMath::FRandRange(-50 * Scale.X, 50 * Scale.X);
					float randomYLocation = FMath::FRandRange(-50 * Scale.Y, 50 * Scale.Y);
					FVector obstacleLocation(location.X + randomXLocation, location.Y + randomXLocation, location.Z);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FText::AsNumber(Scale.X).ToString());

					ObstacleSpawner->Spawn(groundTile, obstacleLocation);
				}
			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("No ground Object"));

			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("No groundSpawner Object"));

	}

}


