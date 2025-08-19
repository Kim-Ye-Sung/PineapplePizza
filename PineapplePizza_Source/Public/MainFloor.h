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
//	class UBoxComponent* StartPoint;				// 스테이지 시작 지점. 투명벽으로 오버랩하여 시작
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* EndPoint;					// 스테이지 끝 지점. 투명벽으로 오버랩하여 끝
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
//	class UArrowComponent* PlayerStartPoint;           // 각 Step별로 Player가 시작할 지점
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool SpawnStart;                                   // 각 Step별로 장애물 스폰을 시작할지 정하는 변수 
//   
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* PlayerRespawnColiision;       // Player가 낙하하면 재시작하기 위한 Collision 
//
//	UFUNCTION()       // Player가 낙하하면 Respawn시켜주는 함수 (BeginOverlap)
//	void PlayerRespawn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool StepProgress;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	class UBoxComponent* CameraChangeCollision;     // 캐릭터가 점프대 사용후 다음 Step 도착시 카메라 움직임을 사용할수 있게 해주는 Coliision
//	                                                // + 캐릭터가 Step에서 낙하 후 리스폰됐을때 카메라를 움직일수 있게 해주는 Collision
//													// 이건 블루프린트에서 관리하기에 cpp에서 보면 그냥 세팅만 해주고 직접 사용하지 않는다. 
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
	class UBoxComponent* StartPoint;				// 스테이지 시작 지점. 투명벽으로 오버랩하여 시작

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EndPoint;					// 스테이지 끝 지점. 투명벽으로 오버랩하여 끝

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
	class UArrowComponent* PlayerStartPoint;           // 각 Step별로 Player가 시작할 지점

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SpawnStart;                                   // 각 Step별로 장애물 스폰을 시작할지 정하는 변수 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* PlayerRespawnColiision;       // Player가 낙하하면 재시작하기 위한 Collision 

	UFUNCTION()       // Player가 낙하하면 Respawn시켜주는 함수 (BeginOverlap)
		void PlayerRespawn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StepProgress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CameraChangeCollision;     // 캐릭터가 점프대 사용후 다음 Step 도착시 카메라 움직임을 사용할수 있게 해주는 Coliision
	// + 캐릭터가 Step에서 낙하 후 리스폰됐을때 카메라를 움직일수 있게 해주는 Collision
	// 이건 블루프린트에서 관리하기에 cpp에서 보면 그냥 세팅만 해주고 직접 사용하지 않는다. 

	UFUNCTION()
	void GameOverCollisionOff();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinStepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StepDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* GameOverCollision;         // 시간초과로 인한 게임오버시 플레이어가 낙하하여 Overlap하면 레벨을 다시 시작하기 위한 콜리전
													// 이것은 여기서 생성만하고 블루프린트에서 사용한다.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* RespawnSound;
};


