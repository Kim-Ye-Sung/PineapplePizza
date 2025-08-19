// Fill out your copyright notice in the Description page of Project Settings.

// ��������� �̷���� �ʿ��� ��ֹ����� ���ӵ��� ������ �����ʰ� ������ �ӵ��� �̵��Ҽ��ְԲ��ϴ� �ڵ��̴�.
// MainGround���� �̰��� �����ϸ�, ���⼭�� �������� ���̵��� ���� �����ϰ� ��ֹ��� ������ �����Ѵ�.
// ��ֹ��� ������ �����ϰ� �����Ѵ�.

#include "TransportMachine.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"   // MainGround.h ���Ͽ��� ���漱�� �������Ƿ� ���⼭ BoxComponent�� ������ �ҷ��ü��� ����. ���� ���⼭�� �̰��� ����������Ѵ�. �׷������� StartPoint�� EndPoint�� ������ �ҷ��ü��� �ִ�.
#include "Components/ArrowComponent.h"
#include "Engine/StaticMesh.h"
#include <Kismet/GameplayStatics.h>                // MainGround�� �ҷ����� ���� ����ؾ���.
#include <Kismet/KismetSystemLibrary.h>      //PrintString�� ����ϱ� ���� �־������.
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

		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);   // �浹 ������ �ϵ� ���� ������ ����

		Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);   	// ��� ä�� Ignore

		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);  // Destructible(==���� MainGround�� Start ä�θ� Destructible��) ä�θ� Overlap

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






	ObstacleMoveSpeed = 1000.0f;    //��ֹ� ������ �̵��ӵ��� ����. �ּ� 2500 ~ 4000.  ����Ұ��� ���ٸ� �⺻ 3000���� ����

	//ObstaclePositions = { FVector(300.0f, 0.0f, 0.0f), FVector(700.0f, 0.0f, 0.0f), FVector(1100.0f, 0.0f, 0.0f), FVector(1500.0f, 0.0f, 0.0f), FVector(1900.0f, 0.0f, 0.0f) };  //��ֹ����� ��ȯ�� ��ġ �迭

	//ObstaclePosition = {FVector(150.0f, 0.0f, 0.0f), FVector(510.0f, 0.0f, 0.0f), FVector(870.0f, 0.0f, 0.0f), FVector(1230.0f, 0.0f, 0.0f), FVector(1590.0f, 0.0f, 0.0f), FVector(1950.0f, 0.0f, 0.0f)};  //��ֹ����� ��ȯ�� ��ġ �迭



}

// Called when the game starts or when spawned
void ATransportMachine::BeginPlay()
{
	Super::BeginPlay();

	//auto diffi = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // ����󿡼� ���ӸŴ��� ���͸� ã��  diffi�� ����

	//DifficultyTransport = Cast<AStage3GameManager>(diffi);          // diffi�� ����ȯ�Ͽ� DIfficultyMachine�� ����

	AActor* Spawner = GetOwner();

	if (Spawner->IsA(AFirstStep::StaticClass()))
	{

		WhatIsStep = 1;

		RandomObstacle = FMath::RandRange(1, 2);  //  ����, �������� ������ ��ֹ� ������ ����
	}
	else if (Spawner->IsA(ASecondStep::StaticClass()))
	{
		WhatIsStep = 2;

		RandomObstacle = FMath::RandRange(3, 4);  //  �볪��, ���� ������ ��ֹ� ������ ����
	}
	else if (Spawner->IsA(AThirdStep::StaticClass()))
	{
		WhatIsStep = 3;

		RandomObstacle = 5; 
	}
	else if (Spawner->IsA(AFourthStep::StaticClass()))
	{
		WhatIsStep = 4;

		RandomObstacle = FMath::RandRange(1, 5);  //  ��� ��ֹ� ������ �����Ͽ� ����
	}


	//RandomObstacle = FMath::RandRange(1, FMath::Clamp(DifficultyTransport->Difficulty, 1, 5));  //Stage3GameManager�� ���̵��� ������ ��ֹ� ������ ����

	//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("% d yes"), RandomObstacle), true, true, FColor::Blue, 15.0f);

	PatternSelect = FMath::RandRange(1, 2);      // ������ �ִ� ��ֹ��� ��ȯ�Ұ����� �������� ����.   1�̸� ���� ����.    2�̸� ���� ����.

	RandomPoint = FMath::RandRange(0, ObstaclePositions.Num() - 1);     // ObstaclePositions �迭�� ���° �ڸ����� ��ֹ��� �����Ұ��ΰ��� �������� ����

	TArray PointArray_1 = ObstaclePositions;       // �� ��ֹ��� ������ ��ȯ�ϱ� ���� ObstaclePoistions�� ������ �迭 ����

	TArray <UArrowComponent*> PointArray_2;        // �� ��ֹ��� ��ȯ�� ��ġ�� �ߺ����� �ʰԲ� ��ġ�� ������ �ִ� �迭 ����

	for (int i = 0; i < 4; i++)
	{
		int32 a = FMath::RandRange(0, PointArray_1.Num() - 1);

		PointArray_2.Add(PointArray_1[a]);

		PointArray_1.RemoveAt(a);
	}

	switch (RandomObstacle)
	{
	case 1:		// ���� ��ֹ�
	{
		
		if (PatternSelect == 1)         // ���� ���� ��ֹ�
		{	
			FVector PositionChange = ObstaclePositions[RandomPoint]->GetRelativeLocation();

			if (RandomPoint == 4)
			{
				PositionChange.X -= 50.0f;

			}

			PositionChange.Y += 230.0f;
			PositionChange.Z += 160.0f;

			ARock* SpawnedRock = GetWorld()->SpawnActor<ARock>(ARock::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //���� ��ֹ� ����

			SpawnedRock->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedRock->PatrolSpeed);   //TransportMachine�� �̵��ӵ��� ����
		}
		else                    //���� �ִ� ��ֹ�
		{
			FVector PositionChange = ObstaclePositions[RandomPoint]->GetRelativeLocation();

			if (RandomPoint == 4)
			{
				PositionChange.X -= 50.0f;

			}

			PositionChange.Y += 230.0f;
			PositionChange.Z += 160.0f;

			ARock* SpawnedRock = GetWorld()->SpawnActor<ARock>(ARock::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //���� ��ֹ� ����

			SpawnedRock->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedRock->PatrolSpeed);    //TransportMachine�� �̵��ӵ��� ����

			SpawnedRock->MoveStop = true;     // ���� ����
		}
	}
		break;

	case 2:   //������ ��ֹ�
	{	
		if (PatternSelect == 1)       // ���� ���� ��ֹ�
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
				APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //������ ��ֹ� �ڿ������� �ణ ��￩�� ����
				SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ
				//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine�� �̵��ӵ��� ����
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
				APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //������ ��ֹ� �ڿ������� �ణ ��￩�� ����
				SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ
				//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine�� �̵��ӵ��� ����
			}
		}
		else                  // ���� �ִ� ��ֹ�
		{
			FVector PositionChange = ObstaclePositions[0]->GetRelativeLocation();
			if (Spawner->IsA(AFirstStep::StaticClass()))
			{
				PositionChange.Z += -20.0f;
			}
			PositionChange.X += 50.0f;
			PositionChange.Z += 80.0f;
			APoliceCar* SpawnedPoliceCar = GetWorld()->SpawnActor<APoliceCar>(APoliceCar::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 9.5f));   //������ ��ֹ� �ڿ������� �ణ ��￩�� ����
			SpawnedPoliceCar->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ

			//ObstacleMoveSpeed = ObstacleMoveSpeedCalculate(SpawnedPoliceCar->PoliceCarPatrolSpeed);    //TransportMachine�� �̵��ӵ��� ����

			SpawnedPoliceCar->MovePattern = true;      // ���� ����
		}
	}
		break;

	case 3:			//�볪�� ��ֹ�
	{	
		FVector PositionChange = ObstaclePositions[2]->GetRelativeLocation();
		PositionChange.X += 30.0f;
		PositionChange.Y += 100.0f;
		PositionChange.Z += 30.0f;
		AWoodenLog* SpawnedWoodenLog = GetWorld()->SpawnActor<AWoodenLog>(AWoodenLog::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //�볪�� ��ֹ� ����
		SpawnedWoodenLog->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);   //��ȯ�� ��ֹ��� Mesh ������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ
	}
		break;

	case 4:      // �� ��ֹ�
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

	case 5:			//���� ��ֹ�
	{
		FVector PositionChange = ObstaclePositions[2]->GetRelativeLocation();
		PositionChange.Y += 500.0f;
		//ObstaclePositions[2].Y += 500.0f;     // ���� ��ֹ� ũ��� ���� y�� ��ǥ ����	
		AGiantWheel* SpawnedGiantWheel = GetWorld()->SpawnActor<AGiantWheel>(AGiantWheel::StaticClass(), PositionChange, FRotator(0.0f, 0.0f, 0.0f));   //���� ��ֹ� ����
		SpawnedGiantWheel->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);    //��ȯ�� ��ֹ��� Mesh ������Ʈ�� �ڽ����� �ٿ� ��� ���Ŵ
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

	AddActorWorldOffset(MovementVector * GetWorld()->GetDeltaSeconds());     // ��ֹ� ������ �̵�
}


//float ATransportMachine::ObstacleMoveSpeedCalculate(float ObstaclePatrolSpeed)   //��ֹ��� ���� �ӵ��� ���� TransportMachine �̵��ӵ� ���
//{
//	float result = 500.0f + (ObstaclePatrolSpeed - 10.0f) * 100.0f;     // �ּ� 2500 ~ �ִ� 4000.  ��ֹ����� ���� �ӵ��� ���� 10 ~ 20���� �����ϰ� ����.
//
//	return result;
//}



