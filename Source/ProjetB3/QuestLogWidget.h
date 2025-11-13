// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJETB3_API UQuestLogWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    // Cette fonction sera appelée quand le widget sera créé
    virtual void NativeConstruct() override;

    // C'est une fonction C++ qui va appeler un événement Blueprint
    UFUNCTION()
    void HandleQuestUpdated(const FQuestObjective& QuestData);

    // C'est l'événement que nous implémenterons dans l'éditeur Blueprint
    // pour mettre à jour le texte à l'écran.
    UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
    void OnQuestDataUpdated(const FQuestObjective& QuestData);

    // Une référence pratique vers notre composant de quêtes
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
    class UQuestComponent* QuestComponent;
};
