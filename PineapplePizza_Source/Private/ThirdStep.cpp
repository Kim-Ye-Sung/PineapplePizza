// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdStep.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

AThirdStep::AThirdStep()
{

	MainMesh->bHiddenInGame = true;

	CameraChangeCollision->SetRelativeLocation(FVector(-3900.0f, 8400.0f, 80.0f));

	PlayerStartPoint->SetRelativeLocation(FVector(-3900.0f, 8400.0f, 30.0f));


	SpawnTime = 2.2f;

	MinStepDistance = 2900.0f;
	MaxStepDistance = 3000.0f;

	StepDistance = MinStepDistance;

}

