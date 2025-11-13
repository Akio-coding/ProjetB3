// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestData.h" // N'oubliez pas d'inclure notre structure !
#include "QuestComponent.generated.h"

// C'est un "signal" que notre UI pourra écouter.
// Quand ce signal est émis, l'UI saura qu'elle doit se mettre à jour.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, const FQuestObjective&, QuestData);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJETB3_API UQuestComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestComponent();

    // La liste des quêtes que le joueur a actuellement
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
    TArray<FActiveQuest> ActiveQuests;

    // Le "signal" de mise à jour pour l'UI
    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestUpdated OnQuestUpdated;

    // Fonction pour ajouter une nouvelle quête
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AddQuest(FActiveQuest NewQuest);
};