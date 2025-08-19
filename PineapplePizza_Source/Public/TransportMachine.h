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
	float ObstacleMoveSpeed;					    // ��ֹ� ������ �̵��ӵ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector MovementVector;                         // ��ֹ� ������ �̵� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RandomObstacle;							    // ��ֹ� ���� ���� ����


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)      // ��ֹ� ��ȯ�� ��ġ �迭
	TArray<UArrowComponent*> ObstaclePositions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)      // ��ֹ� ������ �������� �����̳� ���ĸ� �����ϴ� ���� 
	int32 PatternSelect;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<FVector> RandomPattern;                    // �������� �����̴� ��ֹ� ��ġ �迭



	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class AStage3GameManager* DifficultyTransport;        //���̵��� ���� ��ֹ� ������ ���� ���ӸŴ����� ���� ����

	//UFUNCTION()
	//float ObstacleMoveSpeedCalculate(float ObstaclePatrolSpeed);     // ��ֹ����� ���� �ӵ��� ���� TransportMachine�� �ӵ��� �ٸ��� �ϱ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RandomPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PoliceCarRandomPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 WhatIsStep;

};
