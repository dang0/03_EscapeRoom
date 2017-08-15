// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// assign input actions to grabber
	void SetupInputComponent();

	// look for and assign physics handle
	void FindPhysicsHandleComponent();

	// attempt to grab physics body object within reach, attach to physics handle
	void Grab();

	// release component attached to physics handle
	void Release();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// get line trace end of reach
	FVector GetReachLineEnd();

	// get line trace start of grabber
	FVector GetReachLineStart();

		
private:
	float GrabberReach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;
};
