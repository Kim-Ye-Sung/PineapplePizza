// Fill out your copyright notice in the Description page of Project Settings.


#include "MainFloor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "TransportMachine.h"
#include "Components/BoxComponent.h"
#include "Obstacle.h"
#include "Stage3GameManager.h"	
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>        

// Sets default values
AMainFloor::AMainFloor()
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);


	// 각 Step의 플레이어가 오를 장소
	// 플레이어가 이동할 거리나 기울기등은 언리얼에서 기본 제공하는 SM_Ramp를 기준으로 만들어졌음.
	// 혹시나 게임을 다시 만들게 될 일이 있다면 아래 주석으로 된 크기를 참고하고 만들기를 바람.

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> MainmeshObj(TEXT("/script/engine.staticmesh'/game/levelprototyping/meshes/sm_ramp.sm_ramp'"));
	if (MainmeshObj.Succeeded())
	{
		MainMesh->SetStaticMesh(MainmeshObj.Object);
		MainMesh->SetupAttachment(Scene);
	}

	WaitingPlace = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WaitingPlace"));
	WaitingPlace->SetupAttachment(Scene);

	ObstacleSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ObstacleSpawnPoint"));
	ObstacleSpawnPoint->SetupAttachment(Scene);
	ObstacleSpawnPoint->SetRelativeLocation(FVector(-100.0f, 900.0f, 1350.0f));


	PlayerStartPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerStartPoint"));

	PlayerStartPoint->SetupAttachment(Scene);
	PlayerStartPoint->SetRelativeLocation(FVector(3500.0f, 8500.0f, 150.0f));



	StartPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("StartPoint"));
	StartPoint->SetupAttachment(Scene);													//Scene의 자식 컴포넌트로 설정
	StartPoint->SetRelativeLocation(FVector(1000.0f, 9000.0f, 0.0f));					//오브젝트에서의 위치를 지정
	StartPoint->SetBoxExtent(FVector(6000.0f, 50.0f, 6000.0f));							//스타트 지점의 크기를 설정
	StartPoint->OnComponentEndOverlap.AddDynamic(this, &AMainFloor::OnEndOverlap);	 // 시작지점에서 플레이어와 충돌 시 OnStartOverlap 함수를 실행
	StartPoint->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);         // coliision 채널을 Destructible로 변경




	EndPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("EndPoint"));
	EndPoint->SetupAttachment(Scene);													  //Scene의 자식 컴포넌트로 설정
	EndPoint->SetRelativeLocation(FVector(1000.0f, 0.0f, 1500.0f));					 //오브젝트에서의 위치를 지정
	EndPoint->SetBoxExtent(FVector(1000.0f, 32.0f, 3000.0f));							 // 끝 지점의 크기를 설정


	PlayerRespawnColiision = CreateDefaultSubobject<UBoxComponent>(TEXT("PlayerRespawnColiision"));
	PlayerRespawnColiision->SetupAttachment(Scene);
	PlayerRespawnColiision->SetBoxExtent(FVector(20000.0f, 30000.0f, 4000.0f));
	PlayerRespawnColiision->SetRelativeLocation(FVector(1000.0f, 2350.0f, -9000.0f));
	PlayerRespawnColiision->SetRelativeRotation(FRotator(0.0f, 0.0f, 9.5f));
	PlayerRespawnColiision->OnComponentBeginOverlap.AddDynamic(this, &AMainFloor::PlayerRespawn);


	CameraChangeCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraChangeCollision"));
	CameraChangeCollision->SetupAttachment(Scene);
	CameraChangeCollision->SetRelativeLocation(FVector(3500.0f, 8500.0f, 150.0f));
	CameraChangeCollision->SetBoxExtent(FVector(150.0f, 150.0f, 32.0f));


	GameOverCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("GameOverCollision"));
	GameOverCollision->SetupAttachment(Scene);
	GameOverCollision->SetBoxExtent(FVector(20000.0f, 30000.0f, 4000.0f));
	GameOverCollision->SetRelativeLocation(FVector(1000.0f, 2350.0f, -9000.0f));
	GameOverCollision->SetRelativeRotation(FRotator(0.0f, 0.0f, 9.5f));


	RespawnSound = CreateDefaultSubobject<UAudioComponent>(TEXT("RespawnSound"));
	RespawnSound->SetupAttachment(Scene);
	RespawnSound->bAutoActivate = false;


	SpawnTime = 1.7f;

	CurrentTime = 0.0f;

	Progress = 0.0f;

	SpawnStart = false;      // TransportMachine 스폰을 시작하냐 마느냐 결정하는 변수. false면 스폰하지 않음. 

	StepProgress = true;     // Step의 Progress계산을 하느냐 마느냐를 결정하는 변수. true면 각 Step별로 Progress를 계산하고,
	// JumpPad로 다음 Step으로 이동 시 false로 변경하여 이전 Step의 Progress를 1로 고정

	StepDistance = MinStepDistance;

}

// Called when the game starts or when spawned
void AMainFloor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpawnStart)   //SpawnStart가 true면
	{
		CurrentTime += GetWorld()->GetDeltaSeconds();    // CurrentTime에 DeltaTime을 더함.

		if (CurrentTime >= SpawnTime)     //  현재 시간이 스폰 시간을 넘기면
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			ATransportMachine* SpawnedTransportMachine = GetWorld()->SpawnActor<ATransportMachine>(ATransportMachine::StaticClass(), FVector(ObstacleSpawnPoint->GetComponentLocation()), FRotator(ObstacleSpawnPoint->GetComponentRotation()), SpawnParam);  // ObstaclePoint에서 TransportMachine을 스폰한다.

			if (SpawnedTransportMachine->RandomObstacle == 2 && SpawnedTransportMachine->PatternSelect == 1)     //패턴이 없는 장애물 경찰차이면
			{
				if (SpawnedTransportMachine->PoliceCarRandomPoint == 0)    // TransportMachine의 0번째 자리에서 경찰차가 스폰되면
				{
					//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("0 P")), true, true, FColor::Blue, 15.0f);
					FVector StartComponentPoint = this->StartPoint->GetComponentLocation();         // StartPoint의 위치를 가져오고, 
					StartComponentPoint.Y -= 600.0f;  // StartPoint의 y축으로 -500만큼의 위치를 도착지점으로 잡는다. 
					SpawnedTransportMachine->MovementVector = (StartComponentPoint - SpawnedTransportMachine->ObstaclePositions[0]->GetComponentLocation()).GetSafeNormal() * SpawnedTransportMachine->ObstacleMoveSpeed;    // TransportMachine의 MovementVector를 도착지점으로 설정
				}
				else
				{
					//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("4 P")), true, true, FColor::Blue, 15.0f);
					FVector StartComponentPoint = this->StartPoint->GetComponentLocation();
					StartComponentPoint.Y += 620.0f;
					SpawnedTransportMachine->MovementVector = (StartComponentPoint - SpawnedTransportMachine->ObstaclePositions[4]->GetComponentLocation()).GetSafeNormal() * SpawnedTransportMachine->ObstacleMoveSpeed;
				}
			}
			else
			{
				SpawnedTransportMachine->MovementVector = (this->StartPoint->GetComponentLocation() - this->EndPoint->GetComponentLocation()).GetSafeNormal() * SpawnedTransportMachine->ObstacleMoveSpeed;    //장애물 스포너가 이동할 방향을 결정. 스타트지점을 향해 가야하므로 스타트지점 - 도착지점으로 계산한다. 그리고 normalize를 실행 후 속도를 곱해준다.
			}
			CurrentTime = 0;  // 장애물 스포너 생성시간을 0으로 초기화
		}
	}

	if (StepProgress)
	{
		UpdatePlayerProgress();
	}
	else
	{
		Progress = 1.0f;
	}
}



void AMainFloor::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AObstacle* OtherObstacle = Cast<AObstacle>(OtherComp))    //장애물들
	{
		//UE_LOG(LogTemp, Warning, TEXT("Obstacle"));

		OtherObstacle->SimulateStart();        // 장애물들 날려보내기
		OtherObstacle->PatternEnd = true;      // 장애물 패턴 종료
	}
	else if (Cast<ATransportMachine>(OtherActor))   // 부모
	{
		/*UE_LOG(LogTemp, Warning, TEXT("transport"));*/
		OtherActor->Destroy();   // TransportMachine 파괴
	}
}



void AMainFloor::UpdatePlayerProgress()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  //플레이어를 월드에서 찾음.
	if (!Player)
	{
		return;   //플레이어가 없으면 반환.
	}

	FVector PlayerLocalPos = GetTransform().InverseTransformPosition(Player->GetActorLocation());  // 플레이어의 위치를 Ramp의 로컬 좌표 기준으로 변환

	if (PlayerLocalPos.X >= StartPoint->GetRelativeLocation().X - 1100 && PlayerLocalPos.X <= StartPoint->GetRelativeLocation().X + 1100) //플레이어의 위치가 MainGround의 X축 상에 들어와 있으면
	{
		float StartY = StartPoint->GetRelativeLocation().Y; // StartPoint y축 상대 좌표 가져오기  9000.0f
		float EndY = EndPoint->GetRelativeLocation().Y;     // EndPoint y축 상대 좌표 가져오기    0.0f


		Progress = (StartY - PlayerLocalPos.Y) / (StartY - EndY);   // 진행도 계산
		Progress = FMath::Clamp(Progress, 0.0f, 1.0f);   // 진행도가 0 ~ 1 사이에만 있도록 제한한다. 예를들어 맵 전체가 100퍼센트인데 게임 클리어이후에도 맵 밖으로 계속 갈수 있다면 101%, 102%.... 처럼 계속 100퍼센트를 넘어서 올라갈것이기 때문에 이를 방지한다.

		//Progress *= 100.0f;       //퍼센트로 나타내려면 100을 곱해줘야함. 게임 완성시 삭제하면 됩니다.

		//UE_LOG(LogTemp, Warning, TEXT("진행도: %.2f%%"), Progress);  

		float DistanceProgress = (MaxStepDistance - MinStepDistance) * Progress;
		StepDistance = MinStepDistance + DistanceProgress;
	}
}

void AMainFloor::PlayerRespawn(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Player = Cast<ACharacter>(OtherActor))
	{
		Player->SetActorLocation(this->PlayerStartPoint->GetComponentLocation());

		RespawnSound->Play(0.1f);
	}
}

void AMainFloor::GameOverCollisionOff()
{
	PlayerRespawnColiision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}




