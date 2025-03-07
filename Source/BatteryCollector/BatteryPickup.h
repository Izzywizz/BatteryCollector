// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BATTERYCOLLECTOR_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
	
public:
	ABatteryPickup();

	// Override the WAsCollected function - Use Implemenation becuase it's a blueprint Native Event
	void WasCollected_Implementation() override;
};
