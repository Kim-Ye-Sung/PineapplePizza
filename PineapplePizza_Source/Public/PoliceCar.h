// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "PoliceCar.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API APoliceCar : public AObstacle
{
	GENERATED_BODY()

public:
	APoliceCar();

	virtual void BeginPlay() override;


	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* RoofBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Interior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Window;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* RightFrontWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* RightFrontWheelBrake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LeftFrontWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LeftFrontWheelBrake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* RightBackWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* RightBackWheelBrake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LeftBackWheel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LeftBackWheelBrake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> MeshCollisionSet;    // 몸체를 제외한 다른 메시들의 Collision을 전부 꺼주기 위해 메시들을 담을 배열


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MovePattern;									// 경찰차가 패턴대로 움직이냐 마냐를 결정하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveRightLeft;                                 // 경찰차가 패턴대로 움직일 시 왼쪽으로 움직이냐 오른쪽으로 움직이냐를 결정하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PoliceCarPatrolSpeed;                         // 경찰차가 패턴대로 움직일때 패턴의 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PoliceCarRotation;                         // 경찰차가 자전으로 회전하는 패턴하는 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* PoliceCarArrowPivot;


};
