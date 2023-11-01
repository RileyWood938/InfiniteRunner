// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundSpawner.h"
#include "GameManager.h"

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

	AGroundSpawner* NewActor = GetWorld()->SpawnActor<AGroundSpawner>();
	for (int i = 0; i < 10; i++) {
		FVector location = FVector(0, 1000 * groundTilesSpawned, 0);
		if (NewActor)
		{
			NewActor->Spawn(this, location);
			groundTilesSpawned++;
		}
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

