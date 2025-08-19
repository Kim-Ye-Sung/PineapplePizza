// Fill out your copyright notice in the Description page of Project Settings.

// 바위 장애물
// 외형 설정 및 바위 장애물의 위아래 움직임 패턴을 구현

#include "Rock.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"
#include "TransportMachine.h"
#include "Engine/StaticMesh.h"

ARock::ARock()
{
	PrimaryActorTick.bCanEverTick = true;

    ConstructorHelpers::FObjectFinder<UStaticMesh> RockMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/free_stone_sphere/free_stone_sphere.free_stone_sphere'"));
    if (RockMesh.Succeeded())
    {
        Mesh->SetStaticMesh(RockMesh.Object);
    }

	ConstructorHelpers::FObjectFinder<USoundBase> RockSound(TEXT("/Script/Engine.SoundWave'/Game/_Asset/Sound/StoneSound.StoneSound'"));
	if (RockSound.Succeeded())
	{
		ObstacleSound->SetSound(RockSound.Object);
		ObstacleSound->SetVolumeMultiplier(0.3f);
	}


	ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationAsset(TEXT("/Script/Engine.SoundAttenuation'/Game/_Blueprint/ObstacleAttenuation.ObstacleAttenuation'"));
	if (AttenuationAsset.Succeeded())
	{
		ObstacleSound->AttenuationSettings = AttenuationAsset.Object;
	}







	PatrolSpeed = (float)FMath::RandRange(10, 20);  //위아래로 움직이는 패턴의 속도를 랜덤으로 결정

	RockRotation = FRotator(0.f, 0.f, PatrolSpeed * 10.0f);      //바위 회전 속도를 랜덤으로 결정

    //RockRotation = FRotator(0.f, 0.f, 120.0f);

    Mesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));      //바위 크기 조정

    MoveStop = false;        //바위가 패턴대로 움직이냐 마냐를 결정. true일때 패턴대로 움직임.

    MoveUpDown = true;		//패턴대로 움직일시 위로 오르냐 아래로 내려가느냐를 결정. true일때 위로가고, false일때 아래로 내려감.

    //PatrolSpeed = (float)FMath::RandRange(8,20);    //위아래로 움직이는 패턴의 속도를 랜덤으로 결정

}

void ARock::BeginPlay()
{
	Super::BeginPlay();
	
	ObstacleSound->Play();
}

void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->Mesh->AddLocalRotation(RockRotation * GetWorld()->GetDeltaSeconds());    //바위를 회전시킴

	if (MoveStop && !PatternEnd)		//MoveStop이 true이고, PatternEnd가 false라면 패턴대로 움직임.
	{
		FVector RockLocation = this->Mesh->GetRelativeLocation();      //Mesh의 좌표를 가져옴.

		if (MoveUpDown)   
		{	
			float RockDeltaSpeed = GetWorld()->GetDeltaSeconds() * (PatrolSpeed * 100.0f);    
			RockLocation.Z += RockDeltaSpeed;        // PatrolSpeed만큼 
			Mesh->SetRelativeLocation(RockLocation);   //위로 올라감.

			if (RockLocation.Z >= 1000)    // z축 좌표가 1000을 넘으면 
			{
				MoveUpDown = false;     //아래로 내려갈수 있게끔 MoveUpDown을 false로 변경
			}
		}
		else
		{	
			float RockDeltaSpeed = GetWorld()->GetDeltaSeconds() * (PatrolSpeed *100.0f);
			RockLocation.Z -= RockDeltaSpeed;      //PatrolSpeed만큼
			Mesh->SetRelativeLocation(RockLocation);   //아래로 내려감.

			if (RockLocation.Z <= 0)    // z축 좌표가 0보다 낮으면
			{
				MoveUpDown = true;     // 위로 올라갈수 있게끔 MoveUpDown을 true로 변경
 			}
		}
	}
}