// Fill out your copyright notice in the Description page of Project Settings.


#include "PoliceCar.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

#include "Engine/StaticMesh.h"

APoliceCar::APoliceCar()
{   

    PrimaryActorTick.bCanEverTick = true;

    //----------------------- 단순한 외형 설정 그 이상 그 이하도 아닙니다.  밑에 줄 그어놓은곳 이후로 보시는게 편합니다. --------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------------------------


    RoofBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoofBar"));     // 경찰차 지붕 위에 바     

    Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));    // 경찰차 내부
    
    Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));        //경찰차 창문

    RightFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheel"));    //경찰차 오른쪽 앞바퀴 

    RightFrontWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheelBrake"));  // 경찰차 오른쪽 앞바퀴 브레이크

    LeftFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheel"));   //경찰차 왼쪽 앞바퀴

    LeftFrontWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheelBrake"));  //경찰차 왼쪽 앞바퀴 브레이크

    RightBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheel"));    //경찰차 오른쪽 뒷바퀴

    RightBackWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheelBrake"));   //경찰차 오른쪽 뒷바퀴 브레이크

    LeftBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheel"));     //경찰차 왼쪽 뒷바퀴

    LeftBackWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheelBrake"));   //경찰차 왼쪽 뒷바퀴 브레이크 


    PoliceCarArrowPivot = CreateDefaultSubobject<UArrowComponent>(TEXT("PoliceCarArrowPivot"));
    PoliceCarArrowPivot->SetupAttachment(Scene);


    ConstructorHelpers::FObjectFinder<UStaticMesh> BigBody(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Body_0.CrownVic_Body_0'"));
    if (BigBody.Succeeded())
    {
        Mesh->SetStaticMesh(BigBody.Object);        // 경찰차 몸체 
        Mesh->SetRelativeLocation(FVector(60.0f, 200.0f, 0.0f));
        Mesh->SetupAttachment(PoliceCarArrowPivot);
        Mesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));    // 가로로 내려가기 위해 처음부터 z축 90도로 회전시키고 시작
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> RoofBarMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/Roof_light_bar_0.Roof_light_bar_0'"));
    if (RoofBarMesh.Succeeded())
    {
        RoofBar->SetStaticMesh(RoofBarMesh.Object);
        RoofBar->SetupAttachment(Mesh);
        MeshCollisionSet.Add(RoofBar);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> WindowMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/windows_glass_0.windows_glass_0'"));
    if (WindowMesh.Succeeded())
    {
        Window->SetStaticMesh(WindowMesh.Object);
        Window->SetupAttachment(Mesh);
        MeshCollisionSet.Add(Window);
    }
    
    ConstructorHelpers::FObjectFinder<UStaticMesh> InteriorMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/interior_0.interior_0'"));
    if (InteriorMesh.Succeeded())
    {
        Interior->SetStaticMesh(InteriorMesh.Object);
        Interior->SetupAttachment(Mesh);
        MeshCollisionSet.Add(Interior);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> RightFrontWheelMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Wheel_Ft_R_0.CrownVic_Wheel_Ft_R_0'"));
    if (RightFrontWheelMesh.Succeeded())
    {
        RightFrontWheel->SetStaticMesh(RightFrontWheelMesh.Object);
        RightFrontWheel->SetRelativeLocation(FVector(-100.0f, 230.0f, -40.0f));
        RightFrontWheel->SetupAttachment(Mesh);
        MeshCollisionSet.Add(RightFrontWheel);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> RightFrontWheelBrakeMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_WheelBrake_Ft_R_0.CrownVic_WheelBrake_Ft_R_0'"));
    if (RightFrontWheelBrakeMesh.Succeeded())
    {
        RightFrontWheelBrake->SetStaticMesh(RightFrontWheelBrakeMesh.Object);
        RightFrontWheelBrake->SetRelativeLocation(FVector(-110.0f, 230.0f, -40.0f));
        RightFrontWheelBrake->SetupAttachment(Mesh);
        MeshCollisionSet.Add(RightFrontWheelBrake);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> LeftFrontWheelMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Wheel_Ft_L_0.CrownVic_Wheel_Ft_L_0'"));
    if (LeftFrontWheelMesh.Succeeded())
    {
        LeftFrontWheel->SetStaticMesh(LeftFrontWheelMesh.Object);
        LeftFrontWheel->SetRelativeLocation(FVector(100.0f, 230.0f, -40.0f));
        LeftFrontWheel->SetupAttachment(Mesh);
        MeshCollisionSet.Add(LeftFrontWheel);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> LeftFrontWheelBrakeMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_WheelBrake_Ft_L_0.CrownVic_WheelBrake_Ft_L_0'"));
    if (LeftFrontWheelBrakeMesh.Succeeded())
    {
        LeftFrontWheelBrake->SetStaticMesh(LeftFrontWheelBrakeMesh.Object);
        LeftFrontWheelBrake->SetRelativeLocation(FVector(110.0f, 230.0f, -40.0f));
        LeftFrontWheelBrake->SetupAttachment(Mesh);
        MeshCollisionSet.Add(LeftFrontWheelBrake);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> RightBackWheelMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Wheel_Bk_R_0.CrownVic_Wheel_Bk_R_0'"));
    if (RightBackWheelMesh.Succeeded())
    {
        RightBackWheel->SetStaticMesh(RightBackWheelMesh.Object);
        RightBackWheel->SetRelativeLocation(FVector(-100.0f, -120.0f, -40.0f));
        RightBackWheel->SetupAttachment(Mesh);
        MeshCollisionSet.Add(RightBackWheel);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> RightBackWheelBrakeMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_WheelBrake_Bk_R_0.CrownVic_WheelBrake_Bk_R_0'"));
    if (RightBackWheelBrakeMesh.Succeeded())
    {
        RightBackWheelBrake->SetStaticMesh(RightBackWheelBrakeMesh.Object);
        RightBackWheelBrake->SetRelativeLocation(FVector(-110.0f, -120.0f, -40.0f));
        RightBackWheelBrake->SetupAttachment(Mesh);
        MeshCollisionSet.Add(RightBackWheelBrake);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> LeftBackWheelMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Wheel_Bk_L_0.CrownVic_Wheel_Bk_L_0'"));
    if (LeftBackWheelMesh.Succeeded())
    {
        LeftBackWheel->SetStaticMesh(LeftBackWheelMesh.Object);
        LeftBackWheel->SetRelativeLocation(FVector(100.0f, -120.0f, -40.0f));
        LeftBackWheel->SetupAttachment(Mesh);
        MeshCollisionSet.Add(LeftBackWheel);
    }

    ConstructorHelpers::FObjectFinder<UStaticMesh> LeftBackWheelBrakeMesh(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_WheelBrake_Bk_L_0.CrownVic_WheelBrake_Bk_L_0'"));
    if (LeftBackWheelBrakeMesh.Succeeded())
    {
        LeftBackWheelBrake->SetStaticMesh(LeftBackWheelBrakeMesh.Object);
        LeftBackWheelBrake->SetRelativeLocation(FVector(110.0f, -120.0f, -40.0f));
        LeftBackWheelBrake->SetupAttachment(Mesh);
        MeshCollisionSet.Add(LeftBackWheelBrake);
    }



    // ------------------------------------ 외형 설정 끝 -----------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------

    Mesh->SetRelativeScale3D(FVector(0.72f, 0.72f, 0.72f));           //경찰차 크기 확대

    for (int i = 0; i < MeshCollisionSet.Num(); i++)      // 몸체만 빼고 전부 충돌하지 않게끔 바꿔줌.
    {
        MeshCollisionSet[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);     
    }

    ImpulsePower = 3000.0f;  //경찰차가 StartPoint와 Overlap후 앞으로 나아가는 속도를 변경
    
    MovePattern = false;    // true일때 패턴대로 움직임

    MoveRightLeft = true;    // true일때 오른쪽으로 가고, false일때 왼쪽으로 움직임.

    PoliceCarPatrolSpeed = (float)FMath::RandRange(10, 20);    //좌우로 움직이는 패턴의 속도를 랜덤으로 결정

    PoliceCarRotation = FRotator(0.0f, 540.0f, 0.0f);

    ConstructorHelpers::FObjectFinder<USoundBase>PoliceCarSound(TEXT("/Script/Engine.SoundWave'/Game/_Asset/Sound/Police_Siren.Police_Siren'"));
    if (PoliceCarSound.Succeeded())
    {
        ObstacleSound->SetSound(PoliceCarSound.Object);
        ObstacleSound->SetVolumeMultiplier(0.7f);
    }

    ConstructorHelpers::FObjectFinder<USoundAttenuation> AttenuationAsset(TEXT("/Script/Engine.SoundAttenuation'/Game/_Blueprint/ObstacleAttenuation.ObstacleAttenuation'"));
    if (AttenuationAsset.Succeeded())
    {
        ObstacleSound->AttenuationSettings = AttenuationAsset.Object;
    }

}

void APoliceCar::BeginPlay()
{
    Super::BeginPlay();

    ObstacleSound->Play();
}


void APoliceCar::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MovePattern && !PatternEnd)		//MovePattern이 true이고, PatternEnd가 false라면 패턴대로 움직임.
    {
        FVector PoliceCarLocation = this->PoliceCarArrowPivot->GetRelativeLocation();      //PoliceCarArrowPivot의 좌표를 가져옴.


        this->PoliceCarArrowPivot->AddLocalRotation(PoliceCarRotation * GetWorld()->GetDeltaSeconds());

        if (MoveRightLeft)
        {   
            float PoliceCarDeltaSpeed = (PoliceCarPatrolSpeed *100.0f)* GetWorld()->GetDeltaSeconds();
            PoliceCarLocation.X += PoliceCarDeltaSpeed;    // PoliceCarPatrolSpeed만큼 
            PoliceCarArrowPivot->SetRelativeLocation(PoliceCarLocation);   // 오른쪽으로 움직임.

            if (PoliceCarLocation.X >= 1300.0f)    // X축 좌표가 1400을 넘으면 
            {
                MoveRightLeft = false;     // 왼쪽으로 갈수 있게끔 MoveRightLeft을 false로 변경
            }
        }
        else
        {
            float PoliceCarDeltaSpeed = (PoliceCarPatrolSpeed * 100.0f) * GetWorld()->GetDeltaSeconds();
            PoliceCarLocation.X -= PoliceCarDeltaSpeed;     // PoliceCarPatrolSpeed만큼
            PoliceCarArrowPivot->SetRelativeLocation(PoliceCarLocation);   // 왼쪽으로 움직임.

            if (PoliceCarLocation.X <= 100.0f)    // X축 좌표가 0보다 낮으면
            {
                MoveRightLeft = true;     // 오른쪽로 올라갈수 있게끔 MoveUpDown을 true로 변경
            }
        }
    }
}