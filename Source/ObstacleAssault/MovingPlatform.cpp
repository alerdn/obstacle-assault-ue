// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation += PlatformVelocity * DeltaTime;

	SetActorLocation(CurrentLocation);

	float Distance = FVector::Dist(StartLocation, CurrentLocation);

	if (Distance > DistanceMoved)
	{
		UE_LOG(LogTemp, Display, TEXT("%s's movement overshot by %f"), *GetName(), Distance - DistanceMoved);
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation += MoveDirection * DistanceMoved;
		PlatformVelocity *= -1;
	}
}
