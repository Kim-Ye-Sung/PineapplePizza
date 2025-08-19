// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodenLog.h"
#include "Components/AudioComponent.h"

AWoodenLog::AWoodenLog()
{

	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh>WoodenLogMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/Wood/old_wooden_log_wcokfh1_high1.old_wooden_log_wcokfh1_high1'"));
	if (WoodenLogMesh.Succeeded())
	{
		Mesh->SetStaticMesh(WoodenLogMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> WoodenLogSound(TEXT("/Script/Engine.SoundWave'/Game/_Asset/Sound/WoodSound.WoodSound'"));
	if (WoodenLogSound.Succeeded())
	{
		ObstacleSound->SetSound(WoodenLogSound.Object);
		ObstacleSound->SetVolumeMultiplier(0.7f);
	}

	ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationAsset(TEXT("/Script/Engine.SoundAttenuation'/Game/_Blueprint/ObstacleAttenuation.ObstacleAttenuation'"));
	if (AttenuationAsset.Succeeded())
	{
		ObstacleSound->AttenuationSettings = AttenuationAsset.Object;
	}



	Mesh->SetRelativeScale3D(FVector(5.6f, 2.0f, 2.0f));    //통나무 크기 조절

	LogRotation = FRotator(0.0f, 0.0f, 300.0f);     // 통나무 패턴의 회전 속도 결정
}

void AWoodenLog::BeginPlay()
{
	Super::BeginPlay();

	ObstacleSound->Play();
}


void AWoodenLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FRotator DeltaLogRotation = LogRotation * GetWorld()->GetDeltaSeconds();

	Mesh->AddLocalRotation(LogRotation * GetWorld()->GetDeltaSeconds());    //통나무 회전 패턴 시작
}
