// Fill out your copyright notice in the Description page of Project Settings.


#include "GiantWheel.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"

AGiantWheel::AGiantWheel()
{

	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh>GiantWheelMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/GiantWheel/wooden_wheel_uckpacefa_high1.wooden_wheel_uckpacefa_high1'"));
	if (GiantWheelMesh.Succeeded())
	{
		Mesh->SetStaticMesh(GiantWheelMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<USoundBase> WoodenLogSound(TEXT("/Script/Engine.SoundWave'/Game/_Asset/Sound/WoodSound.WoodSound'"));
	if (WoodenLogSound.Succeeded())
	{
		ObstacleSound->SetSound(WoodenLogSound.Object);
		ObstacleSound->SetVolumeMultiplier(0.7f);
		ObstacleSound->SetPitchMultiplier(0.7f);
	}

	ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationAsset(TEXT("/Script/Engine.SoundAttenuation'/Game/_Blueprint/ObstacleAttenuation2.ObstacleAttenuation2'"));
	if (AttenuationAsset.Succeeded())
	{
		ObstacleSound->AttenuationSettings = AttenuationAsset.Object;
	}




	WheelRotation = FRotator(40.0f, 0.0f, 0.0f);       // 바퀴의 패턴 회전 속도를 결정

	Mesh->SetRelativeScale3D(FVector(35.0f, 12.0f, 35.0f));   // 바퀴 크기 조절

	ArrowPivot = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowPivot"));   //바퀴의 패턴 회전축을 담당할 Arrow컴포넌트 생성

	ArrowPivot->SetupAttachment(Scene);     //Scene을 부모컴포넌트로 설정

	Mesh->SetupAttachment(ArrowPivot);     // Mesh가 Arrow를 축으로 돌아야하므로 Mesh컴포넌트의 부모를 Arrow컴포넌트로 설정

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -1550.0f));   // 바퀴의 위치 조절

}

void AGiantWheel::BeginPlay()
{
	Super::BeginPlay();

	ObstacleSound->Play();

	int32 RandomWheelRotation = FMath::RandRange(1, 2);  // 50% 확률로 바퀴의 회전 방향을 바꿈

	if (RandomWheelRotation == 1)
	{
		WheelRotation *= -1;      //회전 방향 변경
	}
}

void AGiantWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ArrowPivot->AddLocalRotation(WheelRotation * GetWorld()->GetDeltaSeconds());     //바퀴 회전 패턴 시작
}
