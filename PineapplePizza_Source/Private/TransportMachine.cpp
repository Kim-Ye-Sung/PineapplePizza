// Fill out your copyright notice in the Description page of Project Settings.

// 내리막길로 이루어진 맵에서 장애물들이 가속도의 영향을 받지않고 일정한 속도로 이동할수있게끔하는 코드이다.
// MainGround에서 이것을 스폰하며, 여기서는 스테이지 난이도에 따라 랜덤하게 장애물의 종류를 결정한다.
// 장애물의 갯수도 랜덤하게 스폰한다.

#include "TransportMachine.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"   // MainGround.h 파일에는 전방선언만 해줬으므로 여기서 BoxComponent의 정보를 불러올수가 없다. 따라서 여기서도 이것을 선언해줘야한다. 그래야지만 StartPoint와 EndPoint의 정보를 불러올수가 있다.
#include "Components/ArrowComponent.h"
#include "Engine/StaticMesh.h"
#include <Kismet/GameplayStatics.h>                // MainGround를 불러오기 위해 사용해야함.
#include <Kismet/KismetSystemLibrary.h>      //PrintString을 사용하기 위해 넣어줘야함.
#include "Rock.h"
#include "PoliceCar.h"
#include "WoodenLog.h"
#include "GiantWheel.h"
#include "Trap.h"
#include "Stage3GameManager.h"


// Sets default values
ATransportMachine::ATransportMachine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'"));

	if (TempMesh.Succeeded())
	{
		Mesh->SetStaticMesh(TempMesh.Object);

		Mesh->bHiddenInGame = true;

		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);   // 충돌 감지는 하되 물리 반응은 없음

		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);   	// 모든 채널 Ignore

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);  // Destructible(==현재 MainGround의 Start 채널만 Destructible임) 채널만 Overlap

	}


	ObstaclePosition_1 = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePosition_1"));
	ObstaclePosition_1->SetupAttachment(Mesh);
	ObstaclePosition_1->SetRelativeLocation(FVector(300.0f, 0.0f, 0.0f));
	ObstaclePositions.Add(ObstaclePosition_1);

	ObstaclePosition_2 = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePosition_2"));
	ObstaclePosition_2->SetupAttachment(Mesh);
	ObstaclePosition_2->SetRelativeLocation(FVector(700.0f, 0.0f, 0.0f));
	ObstaclePositions.Add(ObstaclePosition_2);

	ObstaclePosition_3 = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePosition_3"));
	ObstaclePosition_3->SetupAttachment(Mesh);
	ObstaclePosition_3->SetRelativeLocation(FVector(1100.0f, 0.0f, 0.0f));
	ObstaclePositions.Add(ObstaclePosition_3);

	ObstaclePosition_4 = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePosition_4"));
	ObstaclePosition_4->SetupAttachment(Mesh);
	ObstaclePosition_4->SetRelativeLocation(FVector(1500.0f, 0.0f, 0.0f));
	ObstaclePositions.Add(ObstaclePosition_4);

	ObstaclePosition_5 = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstaclePosition_5"));
	ObstaclePosition_5->SetupAttachment(Mesh);
	ObstaclePosition_5->SetRelativeLocation(FVector(1900.0f, 0.0f, 0.0f));
	ObstaclePositions.Add(ObstaclePosition_5);






	ObstacleMoveSpeed = 1000.0f;    //장애물 스포너 이동속도를 설정. 최소 2500 ~ 4000.  계산할것이 없다면 기본 3000으로 고정

	//ObstaclePositions = { FVector(300.0f, 0.0f, 0.0f), FVector(700.0f, 0.0f, 0.0f), FVector(1100.0f, 0.0f, 0.0f), FVector(1500.0f, 0.0f, 0.0f), FVector(1900.0f, 0.0f, 0.0f) };  //장애물들이 소환될 위치 배열

	//ObstaclePosition = {FVector(150.0f, 0.0f, 0.0f), FVector(510.0f, 0.0f, 0.0f), FVector(870.0f, 0.0f, 0.0f), FVector(1230.0f, 0.0f, 0.0f), FVector(1590.0f, 0.0f, 0.0f), FVector(1950.0f, 0.0f, 0.0f)};  //장애물들이 소환될 위치 배열



}

// Called when the game starts or when spawned
void ATransportMachine::BeginPlay()
{
	Super::BeginPlay();

	//auto diffi = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // 월드상에서 게임매니저 액터를 찾아  diffi에 저장

	//DifficultyTransport = Cast<AStage3GameManager>(diffi);          // diffi를 형변환하여 DIfficultyMachine에 저장

	AActor* Spawner = GetOwner();

	if (Spawner->IsA(AFirstStep::StaticClass()))
	{

		WhatIsStep = 1;

		RandomObstacle = FMath::RandRange(1, 2);  //  바위, 경찰차중 랜덤한 장애물 종류를 지정
	}
	else if (Spawner->IsA(ASecondStep::StaticClass()))
	{
		WhatIsStep = 2;

		RandomObstacle = FMath::RandRange(3, 4);  //  통나무, 덫중 랜덤한 장애물 종류를 지정
	}
	else if (Spawner->IsA(AThirdStep::StaticClass()))
	{
		WhatIsStep = 3;

		RandomObstacle = 5; 
	}
	else if (Spawner->IsA(AFourthStep::StaticClass()))
	{
		WhatIsStep = 4;

		RandomObstacle = FMath::RandRange(1, 5);  //  모든 장애물 종류중 랜덤하여 지정
	}


	//RandomObstacle = FMath::RandRange(1, FMath::Clamp(DifficultyTransport->Difficulty, 1, 5));  //Stage3GameManager의 난이도로 랜덤한 장애물 종류를 지정

	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("% d yes"), RandomObstacle), true, true, FColor::Blue, 15.0f);

	PatternSelect = FMath::RandRange(1, 2);      // 패턴이 있는 장애물로 소환할것인지 랜덤으로 결정.   1이면 패턴 없음.    2이면 패턴 있음.

	RandomPoint = FMath::RandRange(0, ObstaclePositions.Num() - 1);     // ObstaclePositions 배열의 몇번째 자리에서 장애물을 스폰할것인가를 랜덤으로 정함

	TArray PointArray_1 = ObstaclePositions;       // 덫 장애물을 여러개 소환하기 위해 ObstaclePoistions를 복제한 배열 생성

	TArray <UArrowComponent*> PointArray_2;        // 덫 장애물이 소환될 위치가 중복되지 않게끔 위치를 담을수 있는 배열 생성

	for (int i = 0; i < 4; i++)
	{
		int32 a = FMath::RandRange(0, PointArray_1.Num() - 1);

		PointArray_2.Add(PointArray_1[a]);

		PointArray_1.RemoveAt(a);
	}

	switch (RandomObstacle)
	{
	case 1:		// 바위 장애물
	{
		
		if (PatternSelect == 1)         // 패턴 없는 장애물
		{	
			FVector PositionChange = ObstaclePositions[RandomPoint]->GetRelativeLocation();

			if (RandomPoint == 4)
			{
				PositionChange.X -= 50.0f;

			}

			PositionChange.Y += 230.0f;
			PositionChange.Z += 160.0f;

			ARock* SpawnedRock = GetWorld()->SpawnActor<ARock>(ARock::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //바위 장애물 스폰

			SpawnedRock->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh컴포넌트의 자식으로 붙여 등속 운동시킴

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedRock->PatrolSpeed);   //TransportMachine의 이동속도를 설정
		}
		else                    //패턴 있는 장애물
		{
			FVector PositionChange = ObstaclePositions[RandomPoint]->GetRelativeLocation();

			if (RandomPoint == 4)
			{
				PositionChange.X -= 50.0f;

			}

			PositionChange.Y += 230.0f;
			PositionChange.Z += 160.0f;

			ARock* SpawnedRock = GetWorld()->SpawnActor<ARock>(ARock::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //바위 장애물 스폰

			SpawnedRock->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh컴포넌트의 자식으로 붙여 등속 운동시킴

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedRock->PatrolSpeed);    //TransportMachine의 이동속도를 설정

			SpawnedRock->MoveStop = true;     // 패턴 시작
		}
	}
		break;

	case 2:   //경찰차 장애물
	{	
		if (PatternSelect == 1)       // 패턴 없는 장애물
		{
			PoliceCarRandomPoint = FMath::RandRange(0, 1);         

			if (PoliceCarRandomPoint == 0)
			{	
				FVector PositionChange = ObstaclePositions[0]->GetRelativeLocation();
				if (Spawner->IsA(AFirstStep::StaticClass()))
				{
					PositionChange.Z += -20.0f;
				}
				PositionChange.X += -60.0f;
				PositionChange.Z += 80.0f;
				APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //경찰차 장애물 자연스럽게 약간 기울여서 스폰
				SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh컴포넌트의 자식으로 붙여 등속 운동시킴
				//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine의 이동속도를 설정
			}
			else if (PoliceCarRandomPoint == 1)
			{
				FVector PositionChange = ObstaclePositions[4]->GetRelativeLocation();
				if (Spawner->IsA(AFirstStep::StaticClass()))
				{
					PositionChange.Z += -20.0f;
				}
				PositionChange.X += -300.0f;
				PositionChange.Z += 80.0f;
				APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //경찰차 장애물 자연스럽게 약간 기울여서 스폰
				SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh컴포넌트의 자식으로 붙여 등속 운동시킴
				//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine의 이동속도를 설정
			}
		}
		else                  // 패턴 있는 장애물
		{
			FVector PositionChange = ObstaclePositions[0]->GetRelativeLocation();
			if (Spawner->IsA(AFirstStep::StaticClass()))
			{
				PositionChange.Z += -20.0f;
			}
			PositionChange.X += 50.0f;
			PositionChange.Z += 80.0f;
			APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //경찰차 장애물 자연스럽게 약간 기울여서 스폰
			SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh컴포넌트의 자식으로 붙여 등속 운동시킴

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine의 이동속도를 설정

			SpawnedPoliceCar->MovePattern = true;      // 패턴 시작
		}
	}
		break;

	case 3:			//통나무 장애물
	{	
		FVector PositionChange = ObstaclePositions[2]->GetRelativeLocation();
		PositionChange.X += 30.0f;
		PositionChange.Y += 100.0f;
		PositionChange.Z += 30.0f;
		AWoodenLog* SpawnedWoodenLog = GetWorld()->SpawnActor<AWoodenLog>(AWoodenLog::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //통나무 장애물 스폰
		SpawnedWoodenLog->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //소환된 장애물을 Mesh 컴포넌트의 자식으로 붙여 등속 운동시킴
	}
		break;

	case 4:      // 덫 장애물
	{	
		//FVector PositionChange = ObstaclePositions[RandomPoint]->GetRelativeLocation();
		//PositionChange.Z += 70.0f;
		//ATrap* SpawnedTrap = GetWorld()->SpawnActor<ATrap>(ATrap::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));
		//SpawnedTrap->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		for (int i = 0; i < PointArray_2.Num(); i++)
		{
			FVector PositionChange = PointArray_2[i]->GetRelativeLocation();
			PositionChange.Z += 70.0f;
			ATrap* SpawnedTrap = GetWorld()->SpawnActor<ATrap>(ATrap::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));
			SpawnedTrap->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		}


	}
		break;

	case 5:			//바퀴 장애물
	{
		FVector PositionChange = ObstaclePositions[2]->GetRelativeLocation();
		PositionChange.Y += 500.0f;
		//ObstaclePositions[2].Y += 500.0f;     // 바퀴 장애물 크기로 인해 y축 좌표 조정	
		AGiantWheel* SpawnedGiantWheel = GetWorld()->SpawnActor<AGiantWheel>(AGiantWheel::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //바퀴 장애물 스폰
		SpawnedGiantWheel->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);    //소환된 장애물을 Mesh 컴포넌트의 자식으로 붙여 등속 운동시킴
	}
		break;

	default:
		break;
	}

}

// Called every frame
void ATransportMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(MovementVector * GetWorld()->GetDeltaSeconds());     // 장애물 스포너 이동
}


//float ATransportMachine::ObstacleMoveSpeedCalculate(float ObstaclePatrolSpeed)   //장애물의 패턴 속도에 따른 TransportMachine 이동속도 계산
//{
//	float result = 500.0f + (ObstaclePatrolSpeed - 10.0f) * 100.0f;     // 최소 2500 ~ 최대 4000.  장애물들의 패턴 속도는 전부 10 ~ 20으로 랜덤하게 설정.
//
//	return result;
//}



