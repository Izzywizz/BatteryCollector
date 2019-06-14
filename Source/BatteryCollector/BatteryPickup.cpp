// Fill out your copyright notice in the Description page of Project Settings.


#include "BatteryPickup.h"
#include "Components/StaticMeshComponent.h" //reseolve error regarding physics mesh

//SEt default values  using constructor
ABatteryPickup::ABatteryPickup()
{
    GetMesh()->SetSimulatePhysics(true);
}

void ABatteryPickup::WasCollected_Implementation()
{
    // Use the base pickup behaviour
    Super::WasCollected_Implementation();
    // Destroy the battery
    Destroy();
}