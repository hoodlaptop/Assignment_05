// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MyActor.generated.h"

UCLASS()
class PROJECT_DR_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	// 외부에서 호출하는 함수
	void BeginMove();
	void BeginRotate();
	void TriggerEvent();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// CustomEvent
	void ProcessMovement(float DeltaTime);
	void ProcessRotation(float DeltaTime);

private:
	// 이동 관련
	FVector StartLocation;
	float TargetDistance = 500.0f;
	float MoveSpeed = 200.0f;
	bool bIsMoving = false;

	// 회전 관련
	bool bIsRotating = false;
	FRotator TargetRotation;

	// 스텝 관련
	int32 CurrentStep = 0;
	const int32 MaxSteps = 10;

	float MinDist = 50.0f;
	float MaxDist = 300.0f;
	
	int32 EventCount = 0;
	float TotalMove = 0.0f;

	// 내부 헬퍼 함수
	void SetRandomNextMove();
	void SetRandomNextRotate();
};