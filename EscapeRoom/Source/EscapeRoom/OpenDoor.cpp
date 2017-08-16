// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Find owner
	Owner = GetOwner();
	if (!Owner) {
		UE_LOG(LogTemp, Error, TEXT("Owner not found!"));
		return;
	}

	if (!PressurePlate) {
		UE_LOG(LogTemp,Error, TEXT("%s missing PressurePlate"), *Owner->GetName())
	}


}

void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	// Set door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	// Set door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll trigger volume
	// if ActorThatOpens in is volume
	if (GetTotalMassOfActorsOnPlate() > 30.0f) { // TODO: make into param
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// check if time to close door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > CloseDoorDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() 
{
	float TotalMass = 0.0f;

	// depend on pressure plate
	if (!PressurePlate) { return TotalMass; }

	/// find overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(
		OUT OverlappingActors
	);

	/// iterate and add masses
	for (const auto* Actor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("PressurePlate found: %s"), *(Actor->GetName()));
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

