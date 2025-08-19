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


	// �� Step�� �÷��̾ ���� ���
	// �÷��̾ �̵��� �Ÿ��� ������� �𸮾󿡼� �⺻ �����ϴ� SM_Ramp�� �������� ���������.
	// Ȥ�ó� ������ �ٽ� ����� �� ���� �ִٸ� �Ʒ� �ּ����� �� ũ�⸦ �����ϰ� ����⸦ �ٶ�.

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
	StartPoint->SetupAttachment(Scene);													//Scene�� �ڽ� ������Ʈ�� ����
	StartPoint->SetRelativeLocation(FVector(1000.0f, 9000.0f, 0.0f));					//������Ʈ������ ��ġ�� ����
	StartPoint->SetBoxExtent(FVector(6000.0f, 50.0f, 6000.0f));							//��ŸƮ ������ ũ�⸦ ����
	StartPoint->OnComponentEndOverlap.AddDynamic(this, &AMainFloor::OnEndOverlap);	 // ������������ �÷��̾�� �浹 �� OnStartOverlap �Լ��� ����
	StartPoint->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);         // coliision ä���� Destructible�� ����




	EndPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("EndPoint"));
	EndPoint->SetupAttachment(Scene);													  //Scene�� �ڽ� ������Ʈ�� ����
	EndPoint->SetRelativeLocation(FVector(1000.0f, 0.0f, 1500.0f));					 //������Ʈ������ ��ġ�� ����
	EndPoint->SetBoxExtent(FVector(1000.0f, 32.0f, 3000.0f));							 // �� ������ ũ�⸦ ����


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

	SpawnStart = false;      // TransportMachine ������ �����ϳ� ������ �����ϴ� ����. false�� �������� ����. 

	StepProgress = true;     // Step�� Progress����� �ϴ��� �����ĸ� �����ϴ� ����. true�� �� Step���� Progress�� ����ϰ�,
	// JumpPad�� ���� Step���� �̵� �� false�� �����Ͽ� ���� Step�� Progress�� 1�� ����

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

	if (SpawnStart)   //SpawnStart�� true��
	{
		CurrentTime += GetWorld()->GetDeltaSeconds();    // CurrentTime�� DeltaTime�� ����.

		if (CurrentTime >= SpawnTime)     //  ���� �ð��� ���� �ð��� �ѱ��
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			ATransportMachine* SpawnedTransportMachine = GetWorld()->SpawnActor<ATransportMachine>(ATransportMachine::StaticClass(), FVector(ObstacleSpawnPoint->GetComponentLocation()), FRotator(ObstacleSpawnPoint->GetComponentRotation()), SpawnParam);  // ObstaclePoint���� TransportMachine�� �����Ѵ�.

			if (SpawnedTransportMachine->RandomObstacle == 2 && SpawnedTransportMachine->PatternSelect == 1)     //������ ���� ��ֹ� �������̸�
			{
				if (SpawnedTransportMachine->PoliceCarRandomPoint == 0)    // TransportMachine�� 0��° �ڸ����� �������� �����Ǹ�
				{
					//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("0 P")), true, true, FColor::Blue, 15.0f);
					FVector StartComponentPoint = this->StartPoint->GetComponentLocation();         // StartPoint�� ��ġ�� ��������, 
					StartComponentPoint.Y -= 600.0f;  // StartPoint�� y������ -500��ŭ�� ��ġ�� ������������ ��´�. 
					SpawnedTransportMachine->MovementVector = (StartComponentPoint - SpawnedTransportMachine->ObstaclePositions[0]->GetComponentLocation()).GetSafeNormal() * SpawnedTransportMachine->ObstacleMoveSpeed;    // TransportMachine�� MovementVector�� ������������ ����
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
				SpawnedTransportMachine->MovementVector = (this->StartPoint->GetComponentLocation() - this->EndPoint->GetComponentLocation()).GetSafeNormal() * SpawnedTransportMachine->ObstacleMoveSpeed;    //��ֹ� �����ʰ� �̵��� ������ ����. ��ŸƮ������ ���� �����ϹǷ� ��ŸƮ���� - ������������ ����Ѵ�. �׸��� normalize�� ���� �� �ӵ��� �����ش�.
			}
			CurrentTime = 0;  // ��ֹ� ������ �����ð��� 0���� �ʱ�ȭ
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
	if (AObstacle* OtherObstacle = Cast<AObstacle>(OtherComp))    //��ֹ���
	{
		//UE_LOG(LogTemp, Warning, TEXT("Obstacle"));

		OtherObstacle->SimulateStart();        // ��ֹ��� ����������
		OtherObstacle->PatternEnd = true;      // ��ֹ� ���� ����
	}
	else if (Cast<ATransportMachine>(OtherActor))   // �θ�
	{
		/*UE_LOG(LogTemp, Warning, TEXT("transport"));*/
		OtherActor->Destroy();   // TransportMachine �ı�
	}
}



void AMainFloor::UpdatePlayerProgress()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);  //�÷��̾ ���忡�� ã��.
	if (!Player)
	{
		return;   //�÷��̾ ������ ��ȯ.
	}

	FVector PlayerLocalPos = GetTransform().InverseTransformPosition(Player->GetActorLocation());  // �÷��̾��� ��ġ�� Ramp�� ���� ��ǥ �������� ��ȯ

	if (PlayerLocalPos.X >= StartPoint->GetRelativeLocation().X - 1100 && PlayerLocalPos.X <= StartPoint->GetRelativeLocation().X + 1100) //�÷��̾��� ��ġ�� MainGround�� X�� �� ���� ������
	{
		float StartY = StartPoint->GetRelativeLocation().Y; // StartPoint y�� ��� ��ǥ ��������  9000.0f
		float EndY = EndPoint->GetRelativeLocation().Y;     // EndPoint y�� ��� ��ǥ ��������    0.0f


		Progress = (StartY - PlayerLocalPos.Y) / (StartY - EndY);   // ���൵ ���
		Progress = FMath::Clamp(Progress, 0.0f, 1.0f);   // ���൵�� 0 ~ 1 ���̿��� �ֵ��� �����Ѵ�. ������� �� ��ü�� 100�ۼ�Ʈ�ε� ���� Ŭ�������Ŀ��� �� ������ ��� ���� �ִٸ� 101%, 102%.... ó�� ��� 100�ۼ�Ʈ�� �Ѿ �ö󰥰��̱� ������ �̸� �����Ѵ�.

		//Progress *= 100.0f;       //�ۼ�Ʈ�� ��Ÿ������ 100�� ���������. ���� �ϼ��� �����ϸ� �˴ϴ�.

		//UE_LOG(LogTemp, Warning, TEXT("���൵: %.2f%%"), Progress);  

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




