// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "WoodenLog.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API AWoodenLog : public AObstacle
{
	GENERATED_BODY()

public:
	AWoodenLog();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator LogRotation;								//통나무 회전 속도
	
};
