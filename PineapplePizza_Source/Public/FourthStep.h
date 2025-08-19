// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainFloor.h"
#include "FourthStep.generated.h"

/**
 *
 */
UCLASS()
class PINEAPPLEPIZZA_API AFourthStep : public AMainFloor
{
	GENERATED_BODY()

public:
	AFourthStep();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* CheatSpawn_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* CheatSpawn_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SideCurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SideSpawnTime;


	virtual void Tick(float DeltaTime) override;

	UFUNCTION() // StartPoint에서 충돌 시작 시 실행할 함수
		void GameEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* GameClearRespawnPoint;

};
