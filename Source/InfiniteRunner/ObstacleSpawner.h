// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "ObstacleSpawner.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API AObstacleSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:
	virtual AActor* Spawn(AActor* caller, FVector location) override;
};
