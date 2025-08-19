//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Stage3GameManager.h"
//#include "Components/BoxComponent.h"
//#include <Kismet/GameplayStatics.h>                // World�󿡼� ������Ʈ�� ã���� ��� 
//
//
//// Sets default values
//AStage3GameManager::AStage3GameManager()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	//Difficulty = 2;                     //  ���� ���۽� ���̵��� 2�� ����
//
//	IsStart = false;              // ������ �����ߴ��ĸ� �����ϴ� ����.  FirstStep�� GameStartCollision�� Overlap�ؼ� true�� ����
//
//	PlayTime = 0.0f;            // ��������ð��� ��Ÿ���� ����
//
//	TotalProgress = 0.0f;       //�÷��̾� ���൵�� ��Ÿ���� ����
//
//	NowStep = 0;               // ���� Step�� ��Ÿ���� ����
//	
//	NextTarget = NowStep +1;           // �÷��̾ ���󰡾��� Step�� �����ϴ� ����.
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
//	TotalProgress = ProgressCalculate();    // 3�������� ���൵ ��� 
//
//}
//
//float AStage3GameManager::ProgressCalculate()
//{	
//	float SteptsDistance = 0.0f;     //�� Step�� ���� ����
//	float ProgressRatio = 0.0f;      // ��� Step ���� �� ��(== 3Stage ����)
//	float result = 0.0f;             // �Լ� ��� ��� 
//
//	for (int32 i = 0; i < Steps.Num(); i++)
//	{
//		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;      // �� Step�� ���� ���
//		ProgressRatio += SteptsDistance;     // ��� Step�� ���ؼ� 3Stage�� �� ���̸� ��� 
//	}
//
//	for (int32 i = 0; i < Steps.Num(); i++)
//	{	
//		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;   // �� Step�� ���� ���
//		result += Steps[i]->Progress * SteptsDistance / ProgressRatio;     // �� Step�� Progress ����ؼ� ����.
//	}
//
//	return result;    
//}
//
//
//void AStage3GameManager::WatchActorsInGame(int32 WatchNumber)
//{
//
//	HiddenActor[WatchNumber]->SetActorHiddenInGame(false);     // NowStep ������ ������ ����
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
//		//�ڽĵ鵵 �����
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
#include <Kismet/GameplayStatics.h>                // World�󿡼� ������Ʈ�� ã���� ��� 


// Sets default values
AStage3GameManager::AStage3GameManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Difficulty = 2;                     //  ���� ���۽� ���̵��� 2�� ����

	IsStart = false;              // ������ �����ߴ��ĸ� �����ϴ� ����.  FirstStep�� GameStartCollision�� Overlap�ؼ� true�� ����

	PlayTime = 0.0f;            // ��������ð��� ��Ÿ���� ����

	TimeLimit = 120.0f;

	TextToPlayTime = FormatTimeToString(120.0f - PlayTime);

	TotalProgress = 0.0f;       //�÷��̾� ���� ���൵�� ��Ÿ���� ����

	HighProgress = 0.0f;       // �÷��̾� �ְ� ���൵�� ��Ÿ���� ����

	NowStep = 0;               // ���� Step�� ��Ÿ���� ����

	NextTarget = NowStep + 1;           // �÷��̾ ���󰡾��� Step�� �����ϴ� ����.

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

		TotalProgress = ProgressCalculate();    // 3�������� ���൵ ��� 

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
		if (!IsPlayerJump)     //�÷��̾ �������� �ƴϸ� 
		{
			TextToDistance = FormatDistanceToString(Steps[NowStep]);
		}
		else if (IsPlayerJump)  // �÷��̾ ���� ���̸� 
		{
			TextToDistance = FString::Printf(TEXT("------ m"));
		}
	}


}

float AStage3GameManager::ProgressCalculate()
{
	float SteptsDistance = 0.0f;     //�� Step�� ���� ����
	float ProgressRatio = 0.0f;      // ��� Step ���� �� ��(== 3Stage ����)
	float result = 0.0f;             // �Լ� ��� ��� 

	for (int32 i = 0; i < Steps.Num(); i++)
	{
		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;      // �� Step�� ���� ���
		ProgressRatio += SteptsDistance;     // ��� Step�� ���ؼ� 3Stage�� �� ���̸� ��� 
	}

	for (int32 i = 0; i < Steps.Num(); i++)
	{
		SteptsDistance = Steps[i]->StartPoint->GetRelativeLocation().Y - Steps[i]->EndPoint->GetRelativeLocation().Y;   // �� Step�� ���� ���
		result += Steps[i]->Progress * SteptsDistance / ProgressRatio;     // �� Step�� Progress ����ؼ� ����.
	}

	return result;
}


void AStage3GameManager::WatchActorsInGame(int32 WatchNumber)
{

	HiddenActor[WatchNumber]->SetActorHiddenInGame(false);     // NowStep ������ ������ ����

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

		//�ڽĵ鵵 �����
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






