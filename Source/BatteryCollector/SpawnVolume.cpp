// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/StaticMeshComponent.h" //reseolve error about scenecomponet and root
#include "Templates/SubclassOf.h" // TSubClassOf
#include "Engine/World.h" // World and FActorSpawnParameters
#include "Kismet/KismetMathLibrary.h" // helpful math lib

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the Box Component to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	// Set the rootcomponent to be this Box Component, it will appear at the top of hierarchy
	RootComponent = WhereToSpawn;

	// Set the spawn delay range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	//world timer keeps track of all timers in the world
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);

	
}

// Called every frame - Not this time because its set to false
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	// The Kismet lib has a helpful method that when given a BoxExtent (which is basically the space where the batteries will spawn)
	// And an Origin, it will randomly spwan within this area, which is what we are doing with this Box component

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnPickup()
{
	// If we have set something to spawn:
	if (WhatToSpawn != NULL)
	{
		//check for a valid world
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			/* set the spawn parameters, its so they know who has spawned them and whose started the spawing */
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get a random location to spawn at
			FVector SpawnLocation = GetRandomPointInVolume();
			
			// Get a random rotation for spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// spawn the pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			// Reset the timer and respawn the pickup
			SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
		
	}
	
}