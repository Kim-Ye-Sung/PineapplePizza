// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainFloor.h"
#include "FirstStep.h"
#include "SecondStep.h"
#include "ThirdStep.h"
#include "FourthStep.h"
#include "Stage3GameManager.generated.h"


UCLASS()
class PINEAPPLEPIZZA_API AStage3GameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStage3GameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HighProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AMainFloor*> Steps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFirstStep* FirstStepObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASecondStep* SecondStepObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AThirdStep* ThirdStepObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFourthStep* FourthStepObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextTarget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NowStep;

	UFUNCTION()
	float ProgressCalculate();
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> HiddenActor;

	UFUNCTION()
	void WatchActorsInGame(int32 WatchNumber);

	void HiddenActorsInGame(int32 WatchNumber);   // 1초 뒤 실행할 숨기기 함수 선언

	UFUNCTION()
	FString FormatTimeToString(float TimeInSeconds);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextToPlayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StepRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextToDistance;

	UFUNCTION(BlueprintCallable)
	FString FormatDistanceToString(AMainFloor* Step);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPlayerJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FinalDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameSoundChange;
};
