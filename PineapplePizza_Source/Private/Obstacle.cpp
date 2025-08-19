// Fill out your copyright notice in the Description page of Project Settings.

// ��� ��ֹ����� �θ� �Ǵ� Ŭ�����̴�.

#include "Obstacle.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"			 //ĳ���� ĳ������ ���� �־������.
#include <Kismet/KismetSystemLibrary.h>      //PrintString�� ����ϱ� ���� �־������.
#include "Stage3GameManager.h"
#include "Components/AudioComponent.h"
#include <Kismet/GameplayStatics.h>         // TransportMachine�� �����ϱ� ���� �־������.

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);            // �浹 ������ �ϵ� ���� ������ ����

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);   	// ��� ä�� Ignore

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);  // �÷��̾� ä�θ�  Overlap

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);  // Destructible(==���� MainGround�� Start ä�θ� Destructible��) ä�θ� Overlap

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::ObstacleEffect);      // �÷��̾�� �浹 �� �÷��̾ �о �Լ�

	ObstacleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ObstacleSound"));
	ObstacleSound->SetupAttachment(Scene);
	ObstacleSound->bAutoActivate = false;
	ObstacleSound->bAllowSpatialization = true;


	NnockBackDistance = 1000.0f;      //�÷��̾� �˹� ��ġ

	InitialLifeSpan = 15.0f;        // ��ֹ����� ������� �ð�

	ImpulsePower = 4000.0f;       // ��ֹ��� ������ ���ư��� ��ġ

	PatternEnd = false;        //��ֹ� ���� ���Ḧ ����

	ImpulseVector = FVector(1.0f, 0.0f, 0.0f);   //��ֹ����� ���ư��� ����

	PlayerKnockBackVector = FVector(1.0f, 0.0f, 0.0f);   //��ֹ����� ���ư��� ����

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	//auto diff = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // ����󿡼� ���ӸŴ��� ���͸� �� ã��  diff�� ����

	//DifficultyManager = Cast<AStage3GameManager>(diff);          // diff�� ����ȯ�Ͽ� DIfficultyMachine�� ����
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacle::ObstacleEffect(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{	


		FVector KnockBackVelocity = PlayerKnockBackVector * NnockBackDistance;  // �ӵ� ������ ����

		KnockBackVelocity.Z = 0.0f;      //ĳ���� �ణ ���� ������

		Player->LaunchCharacter(KnockBackVelocity, true, true);   //�÷��̾� �߻�

		//// ����׿� �޽���
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Watch Out!!")), true, true, FColor::Red, 2.0f);

	}
}

void AObstacle::SimulateStart()
{

	//this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);             // ������ ��� �����ϰԲ� ����

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);  // ��� ä�� Block ���·� ����

	Mesh->SetSimulatePhysics(true);  //SimulatePhysics �ѱ�

	ImpulseVector = ImpulseVector * ImpulsePower;  // ��ֹ����� ���ư� ���� ����

	Mesh->AddImpulse(ImpulseVector, FName("None"), true);    //��ֹ� ����������
}

void AObstacle::ObstacleSoundFadeOut()    // 1�ʵ��� ���带 ���̵� �ƿ� ��Ű�� �Լ�
{
	ObstacleSound->FadeOut(1.0f, 0.0f);
}







