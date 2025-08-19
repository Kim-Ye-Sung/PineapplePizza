// Fill out your copyright notice in the Description page of Project Settings.

// 모든 장애물들의 부모가 되는 클래스이다.

#include "Obstacle.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"			 //캐릭터 캐스팅을 위해 넣어줘야함.
#include <Kismet/KismetSystemLibrary.h>      //PrintString을 사용하기 위해 넣어줘야함.
#include "Stage3GameManager.h"
#include "Components/AudioComponent.h"
#include <Kismet/GameplayStatics.h>         // TransportMachine을 생성하기 위해 넣어줘야함.

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);            // 충돌 감지는 하되 물리 반응은 없음

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);   	// 모든 채널 Ignore

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);  // 플레이어 채널만  Overlap

	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Overlap);  // Destructible(==현재 MainGround의 Start 채널만 Destructible임) 채널만 Overlap

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::ObstacleEffect);      // 플레이어와 충돌 시 플레이어를 밀어낼 함수

	ObstacleSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ObstacleSound"));
	ObstacleSound->SetupAttachment(Scene);
	ObstacleSound->bAutoActivate = false;
	ObstacleSound->bAllowSpatialization = true;


	NnockBackDistance = 1000.0f;      //플레이어 넉백 수치

	InitialLifeSpan = 15.0f;        // 장애물들이 사라지는 시간

	ImpulsePower = 4000.0f;       // 장애물이 앞으로 나아가는 수치

	PatternEnd = false;        //장애물 패턴 종료를 결정

	ImpulseVector = FVector(1.0f, 0.0f, 0.0f);   //장애물들이 날아가는 방향

	PlayerKnockBackVector = FVector(1.0f, 0.0f, 0.0f);   //장애물들이 날아가는 방향

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	//auto diff = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // 월드상에서 게임매니저 액터를 를 찾아  diff에 저장

	//DifficultyManager = Cast<AStage3GameManager>(diff);          // diff를 형변환하여 DIfficultyMachine에 저장
	
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


		FVector KnockBackVelocity = PlayerKnockBackVector * NnockBackDistance;  // 속도 스케일 조정

		KnockBackVelocity.Z = 0.0f;      //캐릭터 약간 위로 날리기

		Player->LaunchCharacter(KnockBackVelocity, true, true);   //플레이어 발사

		//// 디버그용 메시지
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Watch Out!!")), true, true, FColor::Red, 2.0f);

	}
}

void AObstacle::SimulateStart()
{

	//this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);             // 물리적 계산 가능하게끔 변경

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);  // 모든 채널 Block 상태로 변경

	Mesh->SetSimulatePhysics(true);  //SimulatePhysics 켜기

	ImpulseVector = ImpulseVector * ImpulsePower;  // 장애물들이 날아갈 방향 결정

	Mesh->AddImpulse(ImpulseVector, FName("None"), true);    //장애물 날려보내기
}

void AObstacle::ObstacleSoundFadeOut()    // 1초동안 사운드를 페이드 아웃 시키는 함수
{
	ObstacleSound->FadeOut(1.0f, 0.0f);
}







