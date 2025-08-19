//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "JumpPad.generated.h"
//
//UCLASS()
//class PINEAPPLEPIZZA_API AJumpPad : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AJumpPad();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};


// JumpPad.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "JumpPad.generated.h"

UCLASS()
class PINEAPPLEPIZZA_API AJumpPad : public AActor
{
    GENERATED_BODY()

public:
    AJumpPad();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    //// �������� ������ �ݸ��� ������Ʈ
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USceneComponent* Scene;


    // �������� �ð��� �޽�
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* PadMesh;

    // ��ǥ ��ġ (�⺻���� 0,0,0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    FVector TargetLocation;

    // �߻� �ð� (�� ����)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float LaunchDuration;

    // �߻� ���� (�ִ� ����)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float LaunchHeight;

    // ĳ���͸� ���� ���·� ������ ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    bool bSetCharacterToJumpState;

    // �߻� ���� ĳ���� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ACharacter* LaunchedCharacter;

    // �߻� ��� �ð�
    float LaunchTime;

    // �ʱ� �߻� ��ġ ����
    FVector StartLocation;

    // �߻� ���� �� ����
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsLaunching;

    // ���� ĳ������ �߷� ������ ����
    float OriginalGravityScale;

    // �ݸ��� �̺�Ʈ ó��
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    // ĳ���� �߻� ����
    void StartLaunch(ACharacter* Character);

    // ĳ���� �߻� ����
    void EndLaunch();

    // �߻� ������Ʈ
    void UpdateLaunch(float DeltaTime);

    // ������ ��ġ ���
    FVector CalculateParabolicPosition(float Alpha);

    // ĳ���͸� ���� ���·� ����
    void SetCharacterToJumpState();

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AStage3GameManager* DifficultyJumpPad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator StartRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator TargetRotation;


    FTimerHandle HideActorsTimerHandle;   // Ÿ�̸� �ڵ� ����


    FTimerHandle WatchActorsTimerHandle;   // Ÿ�̸� �ڵ� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator TargetControlRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInterpolatingRotation;
};
