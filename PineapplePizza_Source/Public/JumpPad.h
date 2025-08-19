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

    //// 점프대의 물리적 콜리전 컴포넌트
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    //UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USceneComponent* Scene;


    // 점프대의 시각적 메시
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* PadMesh;

    // 목표 위치 (기본값은 0,0,0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    FVector TargetLocation;

    // 발사 시간 (초 단위)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float LaunchDuration;

    // 발사 높이 (최대 높이)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    float LaunchHeight;

    // 캐릭터를 점프 상태로 만들지 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Settings")
    bool bSetCharacterToJumpState;

    // 발사 중인 캐릭터 참조
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ACharacter* LaunchedCharacter;

    // 발사 경과 시간
    float LaunchTime;

    // 초기 발사 위치 저장
    FVector StartLocation;

    // 발사 진행 중 여부
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsLaunching;

    // 원래 캐릭터의 중력 스케일 저장
    float OriginalGravityScale;

    // 콜리전 이벤트 처리
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    // 캐릭터 발사 시작
    void StartLaunch(ACharacter* Character);

    // 캐릭터 발사 종료
    void EndLaunch();

    // 발사 업데이트
    void UpdateLaunch(float DeltaTime);

    // 포물선 위치 계산
    FVector CalculateParabolicPosition(float Alpha);

    // 캐릭터를 점프 상태로 설정
    void SetCharacterToJumpState();

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AStage3GameManager* DifficultyJumpPad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator StartRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator TargetRotation;


    FTimerHandle HideActorsTimerHandle;   // 타이머 핸들 선언


    FTimerHandle WatchActorsTimerHandle;   // 타이머 핸들 선언

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator TargetControlRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInterpolatingRotation;
};
