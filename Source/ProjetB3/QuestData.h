// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestReward.h"
#include "QuestData.generated.h"




// 1. Définition de l'Enum Difficulty
UENUM(BlueprintType)
enum class EQuestDifficulty : uint8
{
    Easy          UMETA(DisplayName = "Easy"),
    Medium        UMETA(DisplayName = "Medium"),
    Hard          UMETA(DisplayName = "Hard"),
};


// Objectif de la quête (ex: "Tuer 3 ennemis")
USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

public:
    // Le "Tag" unique pour cet objectif (ex: "KillEnemy", "CollectWood")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FName ObjectiveTag;

    // La description de l'objectif (ex: "Ennemis tués")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText Description;

    // Combien sont nécessaires (ex: 3)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 TargetCount;

    // Combien on en a actuellement (commence à 0)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
    int32 CurrentCount;

    // Constructeur par défaut
    FQuestObjective()
    {
        ObjectiveTag = NAME_None;
        Description = FText::GetEmpty();
        TargetCount = 1;
        CurrentCount = 0;
    }
};


// La structure de la quête principale
USTRUCT(BlueprintType)
struct FActiveQuest
{
    GENERATED_BODY()

public:


    // Titre de la quête (ex: "Nettoyer la zone")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FText Title;
    
    // Difficulté de la quête (ex: "Easy")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    EQuestDifficulty Difficulty;

    // Une quête peut avoir plusieurs objectifs
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FQuestObjective> Objectives;

    // Le tableau des récompenses
    // 'Instanced' est CRUCIAL. Il dit à Unreal que ce tableau 
    // possède des instances uniques de UObjects.
    UPROPERTY(EditAnywhere, Instanced, Category = "Quest")
    TArray<UQuestReward*> Rewards;

    // Pour savoir si la quête est terminée
    UPROPERTY(VisibleInstanceOnly, Category = "Quest")
    bool bIsComplete;

    FActiveQuest()
    {
        bIsComplete = false;
        Difficulty = EQuestDifficulty::Easy;
    }
};

