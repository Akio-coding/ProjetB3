// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"

UQuestComponent::UQuestComponent()
{
    // Nous n'avons pas besoin de "Tick" (mise à jour à chaque frame) pour cela
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::AddQuest(FActiveQuest NewQuest)
{
    ActiveQuests.Add(NewQuest);

    // Émet le signal !
    // L'UI, qui écoute, saura qu'une quête a été ajoutée.
    OnQuestUpdated.Broadcast(NewQuest.Objectives[0]);
}
