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

	FRotator WheelRotation;     //바퀴 회전 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ArrowPivot;           // 바퀴 메쉬의 피벗이 아래쪽에 있어서 회전이 이상하기에 회전축을 담당할 애로우 컴포넌트
};
