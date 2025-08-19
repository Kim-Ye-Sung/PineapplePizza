// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainFloor.h"
#include "FirstStep.generated.h"

/**
 * 
 */
UCLASS()
class PINEAPPLEPIZZA_API AFirstStep : public AMainFloor
{
	GENERATED_BODY()
	
public:
	AFirstStep();

	//virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
