//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Stage3GameManager.h"
//#include "Components/BoxComponent.h"
//#include <Kismet/GameplayStatics.h>                // World상에서 오브젝트를 찾을때 사용 
//
//
//// Sets default values
//AStage3GameManager::AStage3GameManager()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	//Difficulty = 2;                     //  게임 시작시 난이도는 2로 시작
//
//	IsStart = false;              // 게임이 시작했느냐를 결정하는 변수.  FirstStep의 GameStartCollision에 Overlap해서 true로 변경
//
//	PlayTime = 0.0f;            // 게임진행시간을 나타내는 변수
//
//	TotalProgress = 0.0f;       //플레이어 진행도를 나타내는 변수
//
//	NowStep = 0;               // 현재 Step을 나타내는 변수
//	
//	NextTarget = NowStep +1;           // 플레이어가 날라가야할 Step을 결정하는 변수.
//
//}
//
//// Called when the game starts or when spawned
//void AStage3GameManager::BeginPlay()
//{
//	Super::BeginPlay();
//
//	auto FirstObj = UGameplayStatics::GetActorOfClass(GetWorld(), AFirstStep::StaticClass());
//	FirstStepObj = Cast<AFirstStep>(FirstObj);
//
//	auto SecondObj = UGameplayStatics::GetActorOfClass(GetWorld(), ASecondStep::StaticClass());
//	SecondStepObj = Cast<ASecondStep>(SecondObj);
//
//	auto ThirdObj = UGameplayStatics::GetActorOfClass(GetWorld(), AThirdStep::StaticClass());
//	ThirdStepObj = Cast<AThirdStep>(ThirdObj);
//
//	auto FourthObj = UGameplayStatics::GetActorOfClass(GetWorld(), AFourthStep::StaticClass());
//	FourthStepObj = Cast<AFourthStep>(FourthObj);
//
//	Steps.Add(FirstStepObj);   
//	Steps.Add(SecondStepObj);
//	Steps.Add(ThirdStepObj);
//	Steps.Add(FourthStepObj);
//
//	HiddenActorsInGame(NowStep);
//}
//
//// Called every frame
//void AStage3GameManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (IsStart)
//	{
//		PlayTime += GetWorld()->GetDeltaSeconds();
//	}
//
//	TotalProgress = ProgressCalculate();    // 3스테이지 진행도 계산 
//
//}
//
//float AStage3GameManager::ProgressCalculate()
//{	
//	float SteptsDistance = 0.0f;     //각 Step별 길이 변수
//	float ProgressRatio = 0.0f;      // 모든 Step 길이 총 합(== 3Stage 길이)
//	float result = 0.0f;             // 함수 계산 결과 
//
//	for (int32 i = 0; i < Steps.Num(); i++)
//	{
//		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;      // 각 Step별 길이 계산
//		ProgressRatio += SteptsDistance;     // 모든 Step을 더해서 3Stage의 총 길이를 계산 
//	}
//
//	for (int32 i = 0; i < Steps.Num(); i++)
//	{	
//		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;   // 각 Step별 길이 계산
//		result += Steps[i]->Progress * SteptsDistance / ProgressRatio;     // 각 Step별 Progress 계산해서 더함.
//	}
//
//	return result;    
//}
//
//
//void AStage3GameManager::WatchActorsInGame(int32 WatchNumber)
//{
//
//	HiddenActor[WatchNumber]->SetActorHiddenInGame(false);     // NowStep 순번은 숨기지 않음
//
//	TArray<AActor*> AttachedActors;
//	HiddenActor[WatchNumber]->GetAttachedActors(AttachedActors);
//
//	for (AActor* ChildActor : AttachedActors)
//	{
//
//		ChildActor->SetActorHiddenInGame(false);
//
//	}
//}
//
//
//void AStage3GameManager::HiddenActorsInGame(int32 WatchNumber)
//{
//	for (int32 i = 0; i < HiddenActor.Num(); i++)
//	{
//		if (i == WatchNumber)
//		{
//			continue;
//		}
//
//		HiddenActor[i]->SetActorHiddenInGame(true);
//
//		//자식들도 숨기기
//		TArray<AActor*> AttachedActors;
//		HiddenActor[i]->GetAttachedActors(AttachedActors);
//
//		for (AActor* ChildActor : AttachedActors)
//		{
//
//			ChildActor->SetActorHiddenInGame(true);
//
//		}
//	}
//
//}
//
//
//
//
//
//


// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage3GameManager.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>                // World상에서 오브젝트를 찾을때 사용 


// Sets default values
AStage3GameManager::AStage3GameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Difficulty = 2;                     //  게임 시작시 난이도는 2로 시작

	IsStart = false;              // 게임이 시작했느냐를 결정하는 변수.  FirstStep의 GameStartCollision에 Overlap해서 true로 변경

	PlayTime = 0.0f;            // 게임진행시간을 나타내는 변수

	TimeLimit = 120.0f;

	TextToPlayTime = FormatTimeToString(120.0f - PlayTime);

	TotalProgress = 0.0f;       //플레이어 현재 진행도를 나타내는 변수

	HighProgress = 0.0f;       // 플레이어 최고 진행도를 나타내는 변수

	NowStep = 0;               // 현재 Step을 나타내는 변수

	NextTarget = NowStep + 1;           // 플레이어가 날라가야할 Step을 결정하는 변수.

	StepRotation = 0.0f;

	IsPlayerJump = false;

	GameClear = false;
	
	GameStart = false;

	GameSoundChange = false;
}

// Called when the game starts or when spawned
void AStage3GameManager::BeginPlay()
{
	Super::BeginPlay();

	auto FirstObj = UGameplayStatics::GetActorOfClass(GetWorld(), AFirstStep::StaticClass());
	FirstStepObj = Cast<AFirstStep>(FirstObj);

	auto SecondObj = UGameplayStatics::GetActorOfClass(GetWorld(), ASecondStep::StaticClass());
	SecondStepObj = Cast<ASecondStep>(SecondObj);

	auto ThirdObj = UGameplayStatics::GetActorOfClass(GetWorld(), AThirdStep::StaticClass());
	ThirdStepObj = Cast<AThirdStep>(ThirdObj);

	auto FourthObj = UGameplayStatics::GetActorOfClass(GetWorld(), AFourthStep::StaticClass());
	FourthStepObj = Cast<AFourthStep>(FourthObj);

	Steps.Add(FirstStepObj);
	Steps.Add(SecondStepObj);
	Steps.Add(ThirdStepObj);
	Steps.Add(FourthStepObj);

	HiddenActorsInGame(NowStep);

	FinalDistance = Steps[Steps.Num() - 1]->MaxStepDistance;
}

// Called every frame
void AStage3GameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	TextToPlayTime = FormatTimeToString(TimeLimit - PlayTime);

	if (IsStart)
	{
		PlayTime += GetWorld()->GetDeltaSeconds();
		PlayTime = FMath::Clamp(PlayTime, 0.0f, TimeLimit);

		TotalProgress = ProgressCalculate();    // 3스테이지 진행도 계산 

		if (TotalProgress >= HighProgress)
		{
			HighProgress = TotalProgress;
		}
	}

	
	if (PlayTime >= TimeLimit)
	{	

		StepRotation += GetWorld()->GetDeltaSeconds() * 10;

		for (int i = 0; i < Steps.Num(); i++)
		{
			Steps[i]->SpawnStart = false;

			if (i != 0 && StepRotation < 80.5)
			{
				Steps[i]->MainMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, StepRotation));

				Steps[i]->WaitingPlace->SetRelativeRotation(FRotator(0.0f, 0.0f, StepRotation));

				Steps[i]->GameOverCollisionOff();
			}
		}
	}
 

	if (!GameClear)
	{
		if (!IsPlayerJump)     //플레이어가 점프중이 아니면 
		{
			TextToDistance = FormatDistanceToString(Steps[NowStep]);
		}
		else if (IsPlayerJump)  // 플레이어가 점프 중이면 
		{
			TextToDistance = FString::Printf(TEXT("------ m"));
		}
	}


}

float AStage3GameManager::ProgressCalculate()
{
	float SteptsDistance = 0.0f;     //각 Step별 길이 변수
	float ProgressRatio = 0.0f;      // 모든 Step 길이 총 합(== 3Stage 길이)
	float result = 0.0f;             // 함수 계산 결과 

	for (int32 i = 0; i < Steps.Num(); i++)
	{
		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;      // 각 Step별 길이 계산
		ProgressRatio += SteptsDistance;     // 모든 Step을 더해서 3Stage의 총 길이를 계산 
	}

	for (int32 i = 0; i < Steps.Num(); i++)
	{
		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;   // 각 Step별 길이 계산
		result += Steps[i]->Progress * SteptsDistance / ProgressRatio;     // 각 Step별 Progress 계산해서 더함.
	}

	return result;
}


void AStage3GameManager::WatchActorsInGame(int32 WatchNumber)
{

	HiddenActor[WatchNumber]->SetActorHiddenInGame(false);     // NowStep 순번은 숨기지 않음

	TArray<AActor*> AttachedActors;
	HiddenActor[WatchNumber]->GetAttachedActors(AttachedActors);

	for (AActor* ChildActor : AttachedActors)
	{

		ChildActor->SetActorHiddenInGame(false);

	}
}


void AStage3GameManager::HiddenActorsInGame(int32 WatchNumber)
{
	for (int32 i = 0; i < HiddenActor.Num(); i++)
	{
		if (i == WatchNumber)
		{
			continue;
		}

		HiddenActor[i]->SetActorHiddenInGame(true);

		//자식들도 숨기기
		TArray<AActor*> AttachedActors;
		HiddenActor[i]->GetAttachedActors(AttachedActors);

		for (AActor* ChildActor : AttachedActors)
		{

			ChildActor->SetActorHiddenInGame(true);

		}
	}

}

FString AStage3GameManager::FormatTimeToString(float TimeInSeconds)
{
	int Minutes = FMath::FloorToInt(TimeInSeconds / 60.0f);
	int Seconds = FMath::FloorToInt(FMath::Fmod(TimeInSeconds, 60.0f));
	int Hundredths = FMath::FloorToInt(FMath::Fmod(TimeInSeconds, 1.0f) * 100);

	return FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, Hundredths);
}

FString AStage3GameManager::FormatDistanceToString(AMainFloor* Step)
{
	int CalculateDistane = FMath::FloorToInt(Step->StepDistance);

	return FString::Printf(TEXT("%d m"), CalculateDistane);
}






