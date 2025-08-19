// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransportMachine.generated.h"

UCLASS()
class PINEAPPLEPIZZA_API ATransportMachine : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATransportMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ObstacleMoveSpeed;					    // 장애물 스포너 이동속도 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MovementVector;                         // 장애물 스포너 이동 방향 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RandomObstacle;							    // 장애물 종류 랜덤 변수


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstaclePosition_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstaclePosition_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstaclePosition_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstaclePosition_4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstaclePosition_5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)      // 장애물 소환될 위치 배열
	TArray<UArrowComponent*> ObstaclePositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)      // 장애물 스폰시 패턴으로 움직이냐 마냐를 결정하는 변수 
	int32 PatternSelect;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<FVector> RandomPattern;                    // 패턴으로 움직이는 장애물 위치 배열



	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class AStage3GameManager* DifficultyTransport;        //난이도에 따른 장애물 생성을 위해 게임매니저를 담을 변수

	//UFUNCTION()
	//float ObstacleMoveSpeedCalculate(float ObstaclePatrolSpeed);     // 장애물들의 패턴 속도에 따라 TransportMachine의 속도를 다르게 하기

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RandomPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PoliceCarRandomPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 WhatIsStep;

};
