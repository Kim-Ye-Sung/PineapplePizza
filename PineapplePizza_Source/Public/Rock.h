// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API ARock : public AObstacle
{
	GENERATED_BODY()
	
public:
	ARock();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RockRotation;								// 바위 회전 속도


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveStop;										// 바위가 패턴대로 움직이냐 마냐를 결정하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveUpDown;									// 바위가 패턴대로 움직일시 위로 가냐 아래로 가냐를 결정하는 변수


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolSpeed;									//바위가 패턴대로 움직일때 패턴의 속도

};


