// JumpPad.cpp
#include "JumpPad.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Stage3GameManager.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include <Kismet/GameplayStatics.h>   
#include <Kismet/KismetMathLibrary.h>

AJumpPad::AJumpPad()
{
    PrimaryActorTick.bCanEverTick = true;

    //// 컴포넌트 생성
    //TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    //RootComponent = TriggerBox;
    //TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
    //TriggerBox->SetBoxExtent(FVector(50.0f, 50.0f, 20.0f));

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    PadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PadMesh"));

    ConstructorHelpers::FObjectFinder<UStaticMesh> Pad(TEXT("/Script/Engine.StaticMesh'/Game/Materials/cheez-it-baked-snack-crackers-v2/source/cheezeit.cheezeit'"));
    if (Pad.Succeeded())
    {
        PadMesh->SetStaticMesh(Pad.Object);
        PadMesh->SetupAttachment(Scene);
        PadMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        PadMesh->SetRelativeScale3D(FVector(23.0f, 23.0f, 23.0f));
        PadMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        PadMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
        PadMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    }

    // 기본값 설정
    //TargetLocation = FVector(0.0f, 0.0f, 0.0f);
    LaunchDuration = 5.0f;       //원래 1
    LaunchHeight = 20000.0f;     // 원래 500 
    bIsLaunching = false;
    LaunchTime = 0.0f;
    //bSetCharacterToJumpState = true;
    OriginalGravityScale = 1.0f;




}

void AJumpPad::BeginPlay()
{
    Super::BeginPlay();

    // 오버랩 이벤트 등록
    PadMesh->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnOverlapBegin);

    auto diffic = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // 월드상에서 게임매니저 액터를 를 찾아  diffic에 저장

    DifficultyJumpPad = Cast<AStage3GameManager>(diffic);          // diffic를 형변환하여 DIfficultyJumpPad에 저장

}

void AJumpPad::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TargetLocation = DifficultyJumpPad->Steps[DifficultyJumpPad->NextTarget]->PlayerStartPoint->GetComponentLocation();

    TargetRotation = DifficultyJumpPad->Steps[DifficultyJumpPad->NextTarget]->PlayerStartPoint->GetComponentRotation();

    if (DifficultyJumpPad->NextTarget == DifficultyJumpPad->Steps.Num() - 1)
    {
        LaunchDuration = 10.0f;
        LaunchHeight = 40000.0f;
    }

    // 발사 중이면 업데이트
    if (bIsLaunching)
    {
        UpdateLaunch(DeltaTime);
    }
}

void AJumpPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 캐릭터인지 확인
    ACharacter* Character = Cast<ACharacter>(OtherActor);
    if (Character && !bIsLaunching)
    {
        StartLaunch(Character);
    }
}

void AJumpPad::StartLaunch(ACharacter* Character)
{

    DifficultyJumpPad->IsStart = false;

    DifficultyJumpPad->IsPlayerJump = true;

    // 발사 시작 시 설정
    LaunchedCharacter = Character;

    if (DifficultyJumpPad->NowStep == 3)
    {
        LaunchedCharacter->LaunchCharacter(FVector(0.0f, 0.0f, 10000.0f), false, true);

        return;
    }


    StartLocation = LaunchedCharacter->GetActorLocation();


    StartRotation = LaunchedCharacter->GetActorRotation();  //  캐릭터가 도착지점까지 회전하는것을 계산하기 위해 캐릭터의 초기 회전값 받아옴, 

    UE_LOG(LogTemp, Warning, TEXT("%.2f , %.2f, %.2f"), LaunchedCharacter->GetActorRotation().Pitch, LaunchedCharacter->GetActorRotation().Yaw, LaunchedCharacter->GetActorRotation().Roll);

    LaunchTime = 0.0f;
    bIsLaunching = true;

    // 발사 중 캐릭터 움직임 설정
    if (LaunchedCharacter->GetCharacterMovement())
    {
        // 원래 중력 스케일 저장
        OriginalGravityScale = LaunchedCharacter->GetCharacterMovement()->GravityScale;

        // 중력 일시적으로 비활성화 (점프대가 제어)
        LaunchedCharacter->GetCharacterMovement()->GravityScale = 0.0f;

    }

    //DifficultyJumpPad->Steps[DifficultyJumpPad->NextTarget]->SpawnStart = true;     // 다음 Step의 장애물 스폰을 시작

    DifficultyJumpPad->Steps[DifficultyJumpPad->NowStep]->StepProgress = false;

    DifficultyJumpPad->Steps[DifficultyJumpPad->NowStep]->SpawnStart = false;


    if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))          //캐릭터가 목표지점을 향해 몸과 카메라의 방향을 회전
    {
        FVector Direction = (TargetLocation - Character->GetActorLocation()).GetSafeNormal();
        FRotator CameraTargetRotation = Direction.Rotation();

        CameraTargetRotation.Pitch += -10.0f;
        CameraTargetRotation.Yaw += -20.0f;

        // 시야(컨트롤러) 회전
        PC->SetControlRotation(CameraTargetRotation);
    }



    GetWorld()->GetTimerManager().SetTimer(WatchActorsTimerHandle,
        FTimerDelegate::CreateUObject(DifficultyJumpPad, &AStage3GameManager::WatchActorsInGame, DifficultyJumpPad->NextTarget),
        1.0f, // 딜레이
        false // 반복 안 함
    );



    GetWorld()->GetTimerManager().SetTimer(HideActorsTimerHandle,
        FTimerDelegate::CreateUObject(DifficultyJumpPad, &AStage3GameManager::HiddenActorsInGame, DifficultyJumpPad->NextTarget),
        1.0f, // 딜레이
        false // 반복 안 함
    );
}

void AJumpPad::EndLaunch()
{
    // 발사 종료 시 설정
    if (LaunchedCharacter && LaunchedCharacter->GetCharacterMovement())
    {
        // 캐릭터 정확히 목표 위치에 배치
        LaunchedCharacter->SetActorLocation(TargetLocation);

        // 중력 스케일 복원
        LaunchedCharacter->GetCharacterMovement()->GravityScale = OriginalGravityScale;

        // 캐릭터 움직임 복원
        LaunchedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
    }

    // 상태 초기화
    bIsLaunching = false;
    LaunchedCharacter = nullptr;

    DifficultyJumpPad->NowStep += 1;    // 플레이어가 현재 Step을 설정

    if (DifficultyJumpPad->NextTarget + 1 != DifficultyJumpPad->Steps.Num())    // Stage3GameManager의 Steps배열의 갯수만큼 넘지 않으면 
    {
        DifficultyJumpPad->NextTarget = DifficultyJumpPad->NowStep + 1;
    }

    DifficultyJumpPad->IsStart = true;

    DifficultyJumpPad->IsPlayerJump = false;
}

void AJumpPad::UpdateLaunch(float DeltaTime)
{
    // 경과 시간 업데이트
    LaunchTime += DeltaTime;


    // 발사 진행도 계산 (0~1 사이)
    float Alpha = FMath::Clamp(LaunchTime / LaunchDuration, 0.0f, 1.0f);

    // 아직 발사 중  
    if (Alpha < 1.0f && LaunchedCharacter)
    {
        // 포물선 위치 계산하여 캐릭터 위치 설정
        FVector NewLocation = CalculateParabolicPosition(Alpha);
        LaunchedCharacter->SetActorLocation(NewLocation);

        FRotator LinearRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
        LaunchedCharacter->SetActorRotation(LinearRotation);



    }
    // 발사 완료
    else if (LaunchedCharacter)
    {
        EndLaunch();
    }

    //UE_LOG(LogTemp, Warning, TEXT("[JUMP LOG] Time: %f / %f | Alpha: %f"), LaunchTime, LaunchDuration, Alpha);

}

FVector AJumpPad::CalculateParabolicPosition(float Alpha)
{
    // 시작 위치와 목표 위치 사이의 선형 보간
    FVector LinearPosition = FMath::Lerp(StartLocation, TargetLocation, Alpha);

    // 포물선 높이 계산 (sin 곡선으로 위로 솟았다가 내려오는 효과)
    float HeightModifier = FMath::Sin(Alpha * PI) * LaunchHeight;

    // 높이를 더한 최종 위치
    FVector ParabolicPosition = LinearPosition + FVector(0, 0, HeightModifier);

    return ParabolicPosition;
}
