// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondStep.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"


ASecondStep::ASecondStep()
{	

	MainMesh->bHiddenInGame = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> SecondWaitingMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/Step/SecondStep/Table/sm_pokertable.sm_pokertable'"));

	if (SecondWaitingMesh.Succeeded())
	{
		WaitingPlace->SetStaticMesh(SecondWaitingMesh.Object);
		WaitingPlace->SetRelativeLocation(FVector(3780.0f, 8300.0f, -800.0f));
		WaitingPlace->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));
		WaitingPlace->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	}

	CameraChangeCollision->SetRelativeLocation(FVector(3840.0f, 8300.0f, 80.0f));

	PlayerStartPoint->SetRelativeLocation(FVector(3840.0f, 8300.0f, 80.0f));
	PlayerStartPoint->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	SpawnTime = 1.3f;

	MinStepDistance = 480.0f;
	MaxStepDistance = 580.0f;

	StepDistance = MinStepDistance;
}
