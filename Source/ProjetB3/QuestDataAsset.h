// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestData.h"
#include "QuestDataAsset.generated.h"

/**
 * C'est un conteneur de données pour une quête.
 * Il peut être créé et modifié dans l'éditeur.
 */
UCLASS(BlueprintType) // BlueprintType pour qu'on puisse le voir
class PROJETB3_API UQuestDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
    // C'est le "modèle" (template) de notre quête.
    // Toutes les données (Titre, Objectifs, Récompenses) sont ici.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Data")
    FActiveQuest QuestData;
};
