// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "GiantWheel.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API AGiantWheel : public AObstacle
{
	GENERATED_BODY()

public:
	AGiantWheel();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	FRotator WheelRotation;     //���� ȸ�� �ӵ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ArrowPivot;           // ���� �޽��� �ǹ��� �Ʒ��ʿ� �־ ȸ���� �̻��ϱ⿡ ȸ������ ����� �ַο� ������Ʈ
};
