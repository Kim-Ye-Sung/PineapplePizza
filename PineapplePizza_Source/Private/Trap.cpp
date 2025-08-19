// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"

ATrap::ATrap()
{
	PrimaryActorTick.bCanEverTick = true; 

	ConstructorHelpers::FObjectFinder<UStaticMesh> TrapMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/Trap/MouseTrap_texture.MouseTrap_texture'"));

	if (TrapMesh.Succeeded())
	{
		Mesh->SetStaticMesh(TrapMesh.Object);
		Mesh->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	}

	CheatMove = false;


	ConstructorHelpers::FObjectFinder<USoundBase> TrapSound(TEXT("/Script/Engine.SoundWave'/Game/_Asset/Sound/Bear_Trap_Sound_Effect.Bear_Trap_Sound_Effect'"));
	if (TrapSound.Succeeded())
	{
		ObstacleSound->SetSound(TrapSound.Object);
	}
}


void ATrap::Tick(float DeltaTime)
{
	if (CheatMove)
	{
		this->AddActorWorldOffset(CheatMovementVector * GetWorld()->GetDeltaSeconds());
	}
}

void ATrap::ObstacleEffect(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ObstacleSound->Play(0.07f);

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}



