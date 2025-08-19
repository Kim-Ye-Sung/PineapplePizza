// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class PINEAPPLEPIZZA_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacle();

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
	float NnockBackDistance;    //플레이어 넉백 수치

	UFUNCTION()        // 플레이어와 충돌시 플레이어를 밀어낼 함수
		virtual void ObstacleEffect(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintCallable)
	void SimulateStart();   //MainGround의 StartPoint와 충돌 시 장애물 패턴을 끝내고 장애물들을 날려보낼 함수


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpulsePower;    //장애물을 날려보낼 세기

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PatternEnd;       //패턴 정지

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	FVector ImpulseVector;     // 장애물이 날라갈 방향

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AStage3GameManager* DifficultyManager;   // 게임매니저를 담기 위한 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerKnockBackVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* ObstacleSound;

	FTimerHandle SoundFadeOutTimer;

	UFUNCTION()
	void ObstacleSoundFadeOut();


};
