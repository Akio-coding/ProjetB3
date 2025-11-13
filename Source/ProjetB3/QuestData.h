// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestData.generated.h"

// Objectif de la quête (ex: "Tuer 3 ennemis")
USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

public:
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

    // Une quête peut avoir plusieurs objectifs
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FQuestObjective> Objectives;
};
