// Fill out your copyright notice in the Description page of Project Settings.


#include "PoliceCar.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

#include "Engine/StaticMesh.h"

APoliceCar::APoliceCar()
{   

    PrimaryActorTick.bCanEverTick = true;

    //----------------------- �ܼ��� ���� ���� �� �̻� �� ���ϵ� �ƴմϴ�.  �ؿ� �� �׾������ ���ķ� ���ô°� ���մϴ�. --------------------------------
    //---------------------------------------------------------------------------------------------------------------------------------------------------


    RoofBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoofBar"));     // ������ ���� ���� ��     

    Interior = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interior"));    // ������ ����
    
    Window = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window"));        //������ â��

    RightFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheel"));    //������ ������ �չ��� 

    RightFrontWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFrontWheelBrake"));  // ������ ������ �չ��� �극��ũ

    LeftFrontWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheel"));   //������ ���� �չ���

    LeftFrontWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFrontWheelBrake"));  //������ ���� �չ��� �극��ũ

    RightBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheel"));    //������ ������ �޹���

    RightBackWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightBackWheelBrake"));   //������ ������ �޹��� �극��ũ

    LeftBackWheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheel"));     //������ ���� �޹���

    LeftBackWheelBrake = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftBackWheelBrake"));   //������ ���� �޹��� �극��ũ 


    PoliceCarArrowPivot = CreateDefaultSubobject<UArrowComponent>(TEXT("PoliceCarArrowPivot"));
    PoliceCarArrowPivot->SetupAttachment(Scene);


    ConstructorHelpers::FObjectFinder<UStaticMesh> BigBody(TEXT("/Script/Engine.StaticMesh'/Game/_Asset/PoliceCar/CrownVic_Body_0.CrownVic_Body_0'"));
    if (BigBody.Succeeded())
    {
        Mesh->SetStaticMesh(BigBody.Object);        // ������ ��ü 
        Mesh->SetRelativeLocation(FVector(60.0f, 200.0f, 0.0f));
        Mesh->SetupAttachment(PoliceCarArrowPivot);
        Mesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));    // ���η� �������� ���� ó������ z�� 90���� ȸ����Ű�� ����
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



    // ------------------------------------ ���� ���� �� -----------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------------------------------------------

    Mesh->SetRelativeScale3D(FVector(0.72f, 0.72f, 0.72f));           //������ ũ�� Ȯ��

    for (int i = 0; i < MeshCollisionSet.Num(); i++)      // ��ü�� ���� ���� �浹���� �ʰԲ� �ٲ���.
    {
        MeshCollisionSet[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);     
    }

    ImpulsePower = 3000.0f;  //�������� StartPoint�� Overlap�� ������ ���ư��� �ӵ��� ����
    
    MovePattern = false;    // true�϶� ���ϴ�� ������

    MoveRightLeft = true;    // true�϶� ���������� ����, false�϶� �������� ������.

    PoliceCarPatrolSpeed = (float)FMath::RandRange(10, 20);    //�¿�� �����̴� ������ �ӵ��� �������� ����

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

    if (MovePattern && !PatternEnd)		//MovePattern�� true�̰�, PatternEnd�� false��� ���ϴ�� ������.
    {
        FVector PoliceCarLocation = this->PoliceCarArrowPivot->GetRelativeLocation();      //PoliceCarArrowPivot�� ��ǥ�� ������.


        this->PoliceCarArrowPivot->AddLocalRotation(PoliceCarRotation * GetWorld()->GetDeltaSeconds());

        if (MoveRightLeft)
        {   
            float PoliceCarDeltaSpeed = (PoliceCarPatrolSpeed *100.0f)* GetWorld()->GetDeltaSeconds();
            PoliceCarLocation.X += PoliceCarDeltaSpeed;    // PoliceCarPatrolSpeed��ŭ 
            PoliceCarArrowPivot->SetRelativeLocation(PoliceCarLocation);   // ���������� ������.

            if (PoliceCarLocation.X >= 1300.0f)    // X�� ��ǥ�� 1400�� ������ 
            {
                MoveRightLeft = false;     // �������� ���� �ְԲ� MoveRightLeft�� false�� ����
            }
        }
        else
        {
            float PoliceCarDeltaSpeed = (PoliceCarPatrolSpeed * 100.0f) * GetWorld()->GetDeltaSeconds();
            PoliceCarLocation.X -= PoliceCarDeltaSpeed;     // PoliceCarPatrolSpeed��ŭ
            PoliceCarArrowPivot->SetRelativeLocation(PoliceCarLocation);   // �������� ������.

            if (PoliceCarLocation.X <= 100.0f)    // X�� ��ǥ�� 0���� ������
            {
                MoveRightLeft = true;     // �����ʷ� �ö󰥼� �ְԲ� MoveUpDown�� true�� ����
            }
        }
    }
}