// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentStep = 0;
	SetRandomNextMove();
}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentStep < MaxSteps)
	{
		if (bIsMoving)
		{
			ProcessMovement(DeltaTime);
		}
		else if (bIsRotating)
		{
			ProcessRotation(DeltaTime);
		}
	}
}

void AMyActor::BeginMove()
{
	StartLocation = GetActorLocation();
	bIsMoving = true;
}

void AMyActor::BeginRotate()
{
	TargetRotation = GetActorRotation() + FRotator(0.f, 90.f, 0.f);
	bIsRotating = true;
}

void AMyActor::TriggerEvent()
{
	float random = FMath::RandRange(0.f, 1.f);

	if (random < 0.5f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, 
			TEXT("50% Event!!"));
		EventCount++;
	}
}

void AMyActor::ProcessMovement(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	float DistanceTraveled = FVector::Dist(StartLocation, CurrentLocation);
       
	if (DistanceTraveled < TargetDistance)
	{
		float MoveStep = MoveSpeed * DeltaTime;

		if (DistanceTraveled + MoveStep >= TargetDistance)
		{
			float RemainingDist = TargetDistance - DistanceTraveled;
			AddActorLocalOffset(FVector(RemainingDist, 0, 0), true);
			
			TotalMove += TargetDistance;
			
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green,
				FString::Printf(TEXT("Move to %s, %d time"), *CurrentLocation.ToString(), CurrentStep+1));
			
			bIsMoving = false;
			TriggerEvent();
			SetRandomNextRotate();
		}
		else
		{
			AddActorLocalOffset(FVector(MoveStep, 0, 0), true);
		}
	}
}

void AMyActor::ProcessRotation(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 2.0f);
	SetActorRotation(SmoothRotation);

	if (CurrentRotation.Equals(TargetRotation, 1.0f))
	{
		SetActorRotation(TargetRotation);
		bIsRotating = false;
        
		// 회전 끝 -> 횟수 증가 후 다음 이동 준비
		CurrentStep++;
		if (CurrentStep < MaxSteps)
		{
			SetRandomNextMove();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("10회 무작위 이동 완료!"));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, 
				FString::Printf(TEXT("총합 이동 거리 : %f"), TotalMove));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, 
				FString::Printf(TEXT("이벤트 발생 : %d"), EventCount));
			
		}
	}
}

void AMyActor::SetRandomNextMove()
{
	StartLocation = GetActorLocation();
	TargetDistance = FMath::FRandRange(MinDist, MaxDist);
	bIsMoving = true;
}

void AMyActor::SetRandomNextRotate()
{
	float RandomYaw = FMath::FRandRange(-180.0f, 180.0f);
	TargetRotation = GetActorRotation() + FRotator(0.f, RandomYaw, 0.f);
	bIsRotating = true;
}
