// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstStep.h"
#include "Components/BoxComponent.h"
#include "Stage3GameManager.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>    

AFirstStep::AFirstStep()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> Firststepmesh(TEXT("/Script/Engine.StaticMesh'/Game/StylizedPortalShaders/Demo/SM_Plane.SM_Plane'"));
	if (Firststepmesh.Succeeded())
	{
		MainMesh->SetStaticMesh(Firststepmesh.Object);
		MainMesh->SetRelativeLocation(FVector(1000.0f, 4500.0f, 755.0f));
		MainMesh->SetRelativeScale3D(FVector(1.0f, 45.5f, 10.0f));
		MainMesh->SetRelativeRotation(FRotator(-80.5f, -90.0f, 90.0f));
	}

	SpawnTime = 1.5f;

	MinStepDistance = 0.0f;
	MaxStepDistance = 100.0f;

	StepDistance = MinStepDistance;
}

//void AFirstStep::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	Super::OnEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
//
//	if (Cast<ACharacter>(OtherActor))
//	{
//		SpawnStart = true;
//
//		auto Manager = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());
//		AStage3GameManager* GameManager = Cast<AStage3GameManager>(Manager);
//		GameManager->IsStart = true;
//
//		GameManager->GameStart = true;
//
//
//	}
//}


