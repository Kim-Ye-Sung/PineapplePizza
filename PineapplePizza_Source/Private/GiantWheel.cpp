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




	WheelRotation = FRotator(40.0f, 0.0f, 0.0f);       // ������ ���� ȸ�� �ӵ��� ����

	Mesh->SetRelativeScale3D(FVector(35.0f, 12.0f, 35.0f));   // ���� ũ�� ����

	ArrowPivot = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowPivot"));   //������ ���� ȸ������ ����� Arrow������Ʈ ����

	ArrowPivot->SetupAttachment(Scene);     //Scene�� �θ�������Ʈ�� ����

	Mesh->SetupAttachment(ArrowPivot);     // Mesh�� Arrow�� ������ ���ƾ��ϹǷ� Mesh������Ʈ�� �θ� Arrow������Ʈ�� ����

	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -1550.0f));   // ������ ��ġ ����

}

void AGiantWheel::BeginPlay()
{
	Super::BeginPlay();

	ObstacleSound->Play();

	int32 RandomWheelRotation = FMath::RandRange(1, 2);  // 50% Ȯ���� ������ ȸ�� ������ �ٲ�

	if (RandomWheelRotation == 1)
	{
		WheelRotation *= -1;      //ȸ�� ���� ����
	}
}

void AGiantWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ArrowPivot->AddLocalRotation(WheelRotation * GetWorld()->GetDeltaSeconds());     //���� ȸ�� ���� ����
}
