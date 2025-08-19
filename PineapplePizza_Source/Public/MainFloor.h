//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "MainFloor.generated.h"
//
//UCLASS()
//class PINEAPPLEPIZZA_API AMainFloor : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AMainFloor();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class USceneComponent* Scene;
//
//	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	//class UStaticMeshComponent* Mesh;
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UStaticMeshComponent* WaitingPlace;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UArrowComponent* ObstacleSpawnPoint;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* StartPoint;				// �������� ���� ����. �������� �������Ͽ� ����
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* EndPoint;					// �������� �� ����. �������� �������Ͽ� ��
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float SpawnTime;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float CurrentTime;
//
//	UFUNCTION()
//	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float Progress;
//
//	UFUNCTION()
//	void UpdatePlayerProgress();
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UArrowComponent* PlayerStartPoint;           // �� Step���� Player�� ������ ����
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool SpawnStart;                                   // �� Step���� ��ֹ� ������ �������� ���ϴ� ���� 
//   
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* PlayerRespawnColiision;       // Player�� �����ϸ� ������ϱ� ���� Collision 
//
//	UFUNCTION()       // Player�� �����ϸ� Respawn�����ִ� �Լ� (BeginOverlap)
//	void PlayerRespawn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool StepProgress;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* CameraChangeCollision;     // ĳ���Ͱ� ������ ����� ���� Step ������ ī�޶� �������� ����Ҽ� �ְ� ���ִ� Coliision
//	                                                // + ĳ���Ͱ� Step���� ���� �� ������������ ī�޶� �����ϼ� �ְ� ���ִ� Collision
//													// �̰� �������Ʈ���� �����ϱ⿡ cpp���� ���� �׳� ���ø� ���ְ� ���� ������� �ʴ´�. 
//};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainFloor.generated.h"

UCLASS()
class PINEAPPLEPIZZA_API AMainFloor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Scene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MainMesh;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* WaitingPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* ObstacleSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* StartPoint;				// �������� ���� ����. �������� �������Ͽ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EndPoint;					// �������� �� ����. �������� �������Ͽ� ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime;

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Progress;

	UFUNCTION()
	void UpdatePlayerProgress();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* PlayerStartPoint;           // �� Step���� Player�� ������ ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpawnStart;                                   // �� Step���� ��ֹ� ������ �������� ���ϴ� ���� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* PlayerRespawnColiision;       // Player�� �����ϸ� ������ϱ� ���� Collision 

	UFUNCTION()       // Player�� �����ϸ� Respawn�����ִ� �Լ� (BeginOverlap)
		void PlayerRespawn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StepProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CameraChangeCollision;     // ĳ���Ͱ� ������ ����� ���� Step ������ ī�޶� �������� ����Ҽ� �ְ� ���ִ� Coliision
	// + ĳ���Ͱ� Step���� ���� �� ������������ ī�޶� �����ϼ� �ְ� ���ִ� Collision
	// �̰� �������Ʈ���� �����ϱ⿡ cpp���� ���� �׳� ���ø� ���ְ� ���� ������� �ʴ´�. 

	UFUNCTION()
	void GameOverCollisionOff();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinStepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* GameOverCollision;         // �ð��ʰ��� ���� ���ӿ����� �÷��̾ �����Ͽ� Overlap�ϸ� ������ �ٽ� �����ϱ� ���� �ݸ���
													// �̰��� ���⼭ �������ϰ� �������Ʈ���� ����Ѵ�.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* RespawnSound;
};


