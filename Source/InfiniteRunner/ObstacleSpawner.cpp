// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

AActor* AObstacleSpawner::Spawn(AActor* caller, FVector location) {

    UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Script/Engine.Blueprint'/Game/Obstacle.Obstacle'")));

    UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
    if (!SpawnActor)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CANT FIND OBJECT TO SPAWN")));
        return nullptr;
    }

    UClass* SpawnClass = SpawnActor->StaticClass();
    if (SpawnClass == NULL)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("CLASS == NULL")));
        return nullptr;
    }

    UWorld* World = GetWorld();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = caller;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, location, GetActorRotation(), SpawnParams);


    return nullptr;
}