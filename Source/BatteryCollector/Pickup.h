// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS(Blueprintable)
class BATTERYCOLLECTOR_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected: // CAN ONLY BE CHANEGED IN THIS CLASS OR BLUEPRINT
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// True when the pickup can be used, and false when pickup is deactived
	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent* GetMesh() const {return PickupMesh;};

	// Return whether or not the pickup is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool IsActive();

	// Allows other classes to safely change whether or not the pickup is active
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetActive(bool NewPickupState);

	// Function to call when the pickup is collected
	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void WasCollected();
	virtual void WasCollected_Implementation(); //overiiden for child class you only call WasCollected

private:
// Static mesh ro represent the pickup in the level
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PickupMesh;

};
