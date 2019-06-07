// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h" // TSubClassOf
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Pickup.h"
#include "Engine/EngineTypes.h" //FTimeHandle
#include "SpawnVolume.generated.h"

UCLASS(Blueprintable)
class BATTERYCOLLECTOR_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<APickup> WhatToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// REturns the WhereToSpawn subobject
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const {return WhereToSpawn;}

	// Find a random point within the Box Component and return it as a FVector
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	FTimerHandle SpawnTimer;

	// Minimum spawn delay
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;
	// Maximum spawn delay
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

private:
//Box Component to specifiy where pickups should be spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* WhereToSpawn;

	// Handle spawing a new pickup, cannot be called from another class
	void SpawnPickup();

	// Current spawn delay
	float SpawnDelay;
};
