// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJETB3_API UQuestSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void EnemyDied();

	UFUNCTION()
	void ZoneCaptured();
};

