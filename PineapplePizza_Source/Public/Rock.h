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
	FRotator RockRotation;								// ���� ȸ�� �ӵ�


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveStop;										// ������ ���ϴ�� �����̳� ���ĸ� �����ϴ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MoveUpDown;									// ������ ���ϴ�� �����Ͻ� ���� ���� �Ʒ��� ���ĸ� �����ϴ� ����


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolSpeed;									//������ ���ϴ�� �����϶� ������ �ӵ�

};


