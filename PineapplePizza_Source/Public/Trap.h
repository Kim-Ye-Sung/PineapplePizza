// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "Trap.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API ATrap : public AObstacle
{
	GENERATED_BODY()

public:
	ATrap();

	virtual void Tick(float DeltaTime) override;

	virtual void ObstacleEffect(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* Player;


	//UFUNCTION(BlueprintCallable)
	//void PlayerMovementReset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CheatMove;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CheatMovementVector;
};
