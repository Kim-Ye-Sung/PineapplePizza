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

    //// ������Ʈ ����
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

    // �⺻�� ����
    //TargetLocation = FVector(0.0f, 0.0f, 0.0f);
    LaunchDuration = 5.0f;       //���� 1
    LaunchHeight = 20000.0f;     // ���� 500 
    bIsLaunching = false;
    LaunchTime = 0.0f;
    //bSetCharacterToJumpState = true;
    OriginalGravityScale = 1.0f;




}

void AJumpPad::BeginPlay()
{
    Super::BeginPlay();

    // ������ �̺�Ʈ ���
    PadMesh->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnOverlapBegin);

    auto diffic = UGameplayStatics::GetActorOfClass(GetWorld(), AStage3GameManager::StaticClass());   // ����󿡼� ���ӸŴ��� ���͸� �� ã��  diffic�� ����

    DifficultyJumpPad = Cast<AStage3GameManager>(diffic);          // diffic�� ����ȯ�Ͽ� DIfficultyJumpPad�� ����

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

    // �߻� ���̸� ������Ʈ
    if (bIsLaunching)
    {
        UpdateLaunch(DeltaTime);
    }
}

void AJumpPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // ĳ�������� Ȯ��
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

    // �߻� ���� �� ����
    LaunchedCharacter = Character;

    if (DifficultyJumpPad->NowStep == 3)
    {
        LaunchedCharacter->LaunchCharacter(FVector(0.0f, 0.0f, 10000.0f), false, true);

        return;
    }


    StartLocation = LaunchedCharacter->GetActorLocation();


    StartRotation = LaunchedCharacter->GetActorRotation();  //  ĳ���Ͱ� ������������ ȸ���ϴ°��� ����ϱ� ���� ĳ������ �ʱ� ȸ���� �޾ƿ�, 

    UE_LOG(LogTemp, Warning, TEXT("%.2f , %.2f, %.2f"), LaunchedCharacter->GetActorRotation().Pitch, LaunchedCharacter->GetActorRotation().Yaw, LaunchedCharacter->GetActorRotation().Roll);

    LaunchTime = 0.0f;
    bIsLaunching = true;

    // �߻� �� ĳ���� ������ ����
    if (LaunchedCharacter->GetCharacterMovement())
    {
        // ���� �߷� ������ ����
        OriginalGravityScale = LaunchedCharacter->GetCharacterMovement()->GravityScale;

        // �߷� �Ͻ������� ��Ȱ��ȭ (�����밡 ����)
        LaunchedCharacter->GetCharacterMovement()->GravityScale = 0.0f;

    }

    //DifficultyJumpPad->Steps[DifficultyJumpPad->NextTarget]->SpawnStart = true;     // ���� Step�� ��ֹ� ������ ����

    DifficultyJumpPad->Steps[DifficultyJumpPad->NowStep]->StepProgress = false;

    DifficultyJumpPad->Steps[DifficultyJumpPad->NowStep]->SpawnStart = false;


    if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))          //ĳ���Ͱ� ��ǥ������ ���� ���� ī�޶��� ������ ȸ��
    {
        FVector Direction = (TargetLocation - Character->GetActorLocation()).GetSafeNormal();
        FRotator CameraTargetRotation = Direction.Rotation();

        CameraTargetRotation.Pitch += -10.0f;
        CameraTargetRotation.Yaw += -20.0f;

        // �þ�(��Ʈ�ѷ�) ȸ��
        PC->SetControlRotation(CameraTargetRotation);
    }



    GetWorld()->GetTimerManager().SetTimer(WatchActorsTimerHandle,
        FTimerDelegate::CreateUObject(DifficultyJumpPad, &AStage3GameManager::WatchActorsInGame, DifficultyJumpPad->NextTarget),
        1.0f, // ������
        false // �ݺ� �� ��
    );



    GetWorld()->GetTimerManager().SetTimer(HideActorsTimerHandle,
        FTimerDelegate::CreateUObject(DifficultyJumpPad, &AStage3GameManager::HiddenActorsInGame, DifficultyJumpPad->NextTarget),
        1.0f, // ������
        false // �ݺ� �� ��
    );
}

void AJumpPad::EndLaunch()
{
    // �߻� ���� �� ����
    if (LaunchedCharacter && LaunchedCharacter->GetCharacterMovement())
    {
        // ĳ���� ��Ȯ�� ��ǥ ��ġ�� ��ġ
        LaunchedCharacter->SetActorLocation(TargetLocation);

        // �߷� ������ ����
        LaunchedCharacter->GetCharacterMovement()->GravityScale = OriginalGravityScale;

        // ĳ���� ������ ����
        LaunchedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
    }

    // ���� �ʱ�ȭ
    bIsLaunching = false;
    LaunchedCharacter = nullptr;

    DifficultyJumpPad->NowStep += 1;    // �÷��̾ ���� Step�� ����

    if (DifficultyJumpPad->NextTarget + 1 != DifficultyJumpPad->Steps.Num())    // Stage3GameManager�� Steps�迭�� ������ŭ ���� ������ 
    {
        DifficultyJumpPad->NextTarget = DifficultyJumpPad->NowStep + 1;
    }

    DifficultyJumpPad->IsStart = true;

    DifficultyJumpPad->IsPlayerJump = false;
}

void AJumpPad::UpdateLaunch(float DeltaTime)
{
    // ��� �ð� ������Ʈ
    LaunchTime += DeltaTime;


    // �߻� ���൵ ��� (0~1 ����)
    float Alpha = FMath::Clamp(LaunchTime / LaunchDuration, 0.0f, 1.0f);

    // ���� �߻� ��  
    if (Alpha < 1.0f && LaunchedCharacter)
    {
        // ������ ��ġ ����Ͽ� ĳ���� ��ġ ����
        FVector NewLocation = CalculateParabolicPosition(Alpha);
        LaunchedCharacter->SetActorLocation(NewLocation);

        FRotator LinearRotation = FMath::Lerp(StartRotation, TargetRotation, Alpha);
        LaunchedCharacter->SetActorRotation(LinearRotation);



    }
    // �߻� �Ϸ�
    else if (LaunchedCharacter)
    {
        EndLaunch();
    }

    //UE_LOG(LogTemp, Warning, TEXT("[JUMP LOG] Time: %f / %f | Alpha: %f"), LaunchTime, LaunchDuration, Alpha);

}

FVector AJumpPad::CalculateParabolicPosition(float Alpha)
{
    // ���� ��ġ�� ��ǥ ��ġ ������ ���� ����
    FVector LinearPosition = FMath::Lerp(StartLocation, TargetLocation, Alpha);

    // ������ ���� ��� (sin ����� ���� �ھҴٰ� �������� ȿ��)
    float HeightModifier = FMath::Sin(Alpha * PI) * LaunchHeight;

    // ���̸� ���� ���� ��ġ
    FVector ParabolicPosition = LinearPosition + FVector(0, 0, HeightModifier);

    return ParabolicPosition;
}
