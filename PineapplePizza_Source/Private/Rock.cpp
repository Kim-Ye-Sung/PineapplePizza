// Fill out your copyright notice in the Description page of Project Settings.

// ���� ��ֹ�
// ���� ���� �� ���� ��ֹ��� ���Ʒ� ������ ������ ����

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







	PatrolSpeed = (float)FMath::RandRange(10, 20);  //���Ʒ��� �����̴� ������ �ӵ��� �������� ����

	RockRotation = FRotator(0.f, 0.f, PatrolSpeed * 10.0f);      //���� ȸ�� �ӵ��� �������� ����

    //RockRotation = FRotator(0.f, 0.f, 120.0f);

    Mesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));      //���� ũ�� ����

    MoveStop = false;        //������ ���ϴ�� �����̳� ���ĸ� ����. true�϶� ���ϴ�� ������.

    MoveUpDown = true;		//���ϴ�� �����Ͻ� ���� ������ �Ʒ��� ���������ĸ� ����. true�϶� ���ΰ���, false�϶� �Ʒ��� ������.

    //PatrolSpeed = (float)FMath::RandRange(8,20);    //���Ʒ��� �����̴� ������ �ӵ��� �������� ����

}

void ARock::BeginPlay()
{
	Super::BeginPlay();
	
	ObstacleSound->Play();
}

void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->Mesh->AddLocalRotation(RockRotation * GetWorld()->GetDeltaSeconds());    //������ ȸ����Ŵ

	if (MoveStop && !PatternEnd)		//MoveStop�� true�̰�, PatternEnd�� false��� ���ϴ�� ������.
	{
		FVector RockLocation = this->Mesh->GetRelativeLocation();      //Mesh�� ��ǥ�� ������.

		if (MoveUpDown)   
		{	
			float RockDeltaSpeed = GetWorld()->GetDeltaSeconds() * (PatrolSpeed * 100.0f);    
			RockLocation.Z += RockDeltaSpeed;        // PatrolSpeed��ŭ 
			Mesh->SetRelativeLocation(RockLocation);   //���� �ö�.

			if (RockLocation.Z >= 1000)    // z�� ��ǥ�� 1000�� ������ 
			{
				MoveUpDown = false;     //�Ʒ��� �������� �ְԲ� MoveUpDown�� false�� ����
			}
		}
		else
		{	
			float RockDeltaSpeed = GetWorld()->GetDeltaSeconds() * (PatrolSpeed *100.0f);
			RockLocation.Z -= RockDeltaSpeed;      //PatrolSpeed��ŭ
			Mesh->SetRelativeLocation(RockLocation);   //�Ʒ��� ������.

			if (RockLocation.Z <= 0)    // z�� ��ǥ�� 0���� ������
			{
				MoveUpDown = true;     // ���� �ö󰥼� �ְԲ� MoveUpDown�� true�� ����
 			}
		}
	}
}