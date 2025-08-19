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
	TArray<UStaticMeshComponent*> MeshCollisionSet;    // ��ü�� ������ �ٸ� �޽õ��� Collision�� ���� ���ֱ� ���� �޽õ��� ���� �迭


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MovePattern;									// �������� ���ϴ�� �����̳� ���ĸ� �����ϴ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveRightLeft;                                 // �������� ���ϴ�� ������ �� �������� �����̳� ���������� �����̳ĸ� �����ϴ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PoliceCarPatrolSpeed;                         // �������� ���ϴ�� �����϶� ������ �ӵ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PoliceCarRotation;                         // �������� �������� ȸ���ϴ� �����ϴ� �ӵ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* PoliceCarArrowPivot;


};
