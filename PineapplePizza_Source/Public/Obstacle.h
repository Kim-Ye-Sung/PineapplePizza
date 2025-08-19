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
	float NnockBackDistance;    //�÷��̾� �˹� ��ġ

	UFUNCTION()        // �÷��̾�� �浹�� �÷��̾ �о �Լ�
		virtual void ObstacleEffect(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintCallable)
	void SimulateStart();   //MainGround�� StartPoint�� �浹 �� ��ֹ� ������ ������ ��ֹ����� �������� �Լ�


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ImpulsePower;    //��ֹ��� �������� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool PatternEnd;       //���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	FVector ImpulseVector;     // ��ֹ��� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AStage3GameManager* DifficultyManager;   // ���ӸŴ����� ��� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerKnockBackVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* ObstacleSound;

	FTimerHandle SoundFadeOutTimer;

	UFUNCTION()
	void ObstacleSoundFadeOut();


};
