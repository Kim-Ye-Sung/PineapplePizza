// Fill out your copyright notice in the Description page of Project Settings.


#include "FourthStep.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Trap.h"
#include "Stage3GameManager.h"
#include <Kismet/GameplayStatics.h>                // World상에서 오브젝트를 찾을때 사용 

AFourthStep::AFourthStep()
{
	
	MainMesh->bHiddenInGame = true;
	
	WaitingPlace->bHiddenInGame = true;



	PlayerStartPoint->SetRelativeLocation(FVector(1000.0f, 17850.0f, 80.0f));
	PlayerStartPoint->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ObstacleSpawnPoint->SetRelativeLocation(FVector(-100.0f, 1800.0f, 2700.0f));

	StartPoint->SetRelativeLocation(FVector(1000.0f, 18000.0f, 0.0f));

	EndPoint->SetRelativeLocation(FVector(1000.0f, 360.0f, 2940.0f));
	EndPoint->OnComponentEndOverlap.AddDynamic(this, &AFourthStep::GameEnd);

	PlayerRespawnColiision->SetRelativeLocation(FVector(1000.0f, 7500.0f, -10000.0f));
	PlayerRespawnColiision->SetBoxExtent(FVector(30000.0f, 35000.0f, 4000.0f));

	GameOverCollision->SetRelativeLocation(FVector(1000.0f, 7500.0f, -10000.0f));
	GameOverCollision->SetBoxExtent(FVector(30000.0f, 35000.0f, 4000.0f));

	CheatSpawn_1 = CreateDefaultSubobject<UArrowComponent>(TEXT("ChearSpawn_1"));
	CheatSpawn_1->SetupAttachment(Scene);
	CheatSpawn_1->SetRelativeLocation(FVector(-130.0f, 1800.0f, 2600.0f));

	CheatSpawn_2 = CreateDefaultSubobject<UArrowComponent>(TEXT("CheatSpawn_2"));
	CheatSpawn_2->SetupAttachment(Scene);
	CheatSpawn_2->SetRelativeLocation(FVector(2130.0f, 1800.0f, 2600.0f));

	CameraChangeCollision->SetRelativeLocation(FVector(1000.0f, 17850.0f, 80.0f));


	GameClearRespawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("GameClearRespawnPoint"));
	GameClearRespawnPoint->SetupAttachment(Scene);
	GameClearRespawnPoint->SetRelativeLocation(FVector(1000.0f, 360.0f, 3050.0f));
	GameClearRespawnPoint->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));



	SideCurrentTime = 0.0f;

	SideSpawnTime = 0.5f;


	SpawnTime = 1.0f;

	MinStepDistance = 195427.0f;

	MaxStepDistance = 999999.0f;

	StepDistance = MinStepDistance;
}

void AFourthStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnStart)
	{
		SideCurrentTime += GetWorld()->GetDeltaSeconds();

		if (SideCurrentTime >= SideSpawnTime)
		{
			ATrap* CheatTrap_1 = GetWorld()->SpawnActor<ATrap>(ATrap::StaticClass(), FVector(CheatSpawn_1->GetComponentLocation()), FRotator(CheatSpawn_1->GetComponentRotation()));

			UE_LOG(LogTemp, Warning, TEXT("SPawn1"));

			ATrap* CheatTrap_2 = GetWorld()->SpawnActor<ATrap>(ATrap::StaticClass(), FVector(CheatSpawn_2->GetComponentLocation()), FRotator(CheatSpawn_2->GetComponentRotation()));

			UE_LOG(LogTemp, Warning, TEXT("SPawn2"));

			CheatTrap_1->CheatMove = true;
			CheatTrap_2->CheatMove = true;

			CheatTrap_1->CheatMovementVector = (StartPoint->GetComponentLocation() - EndPoint->GetComponentLocation()).GetSafeNormal() * 3000;
			CheatTrap_2->CheatMovementVector = (StartPoint->GetComponentLocation() - EndPoint->GetComponentLocation()).GetSafeNormal() * 3000;

			SideCurrentTime = 0.0f;
		}
	}
}

void AFourthStep::GameEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Manager = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());
	AStage3GameManager* GameManager = Cast<AStage3GameManager>(Manager);
	
	if (GameManager->PlayTime >= GameManager->TimeLimit)
	{
		return;
	}

	if (Cast<ACharacter>(OtherActor))
	{
		GameManager->IsStart = false;

		GameManager->GameStart = false;

		GameManager->GameClear = true;

		SpawnStart = false;

		PlayerStartPoint->SetRelativeLocation(FVector(GameClearRespawnPoint->GetRelativeLocation()));
	}
}
