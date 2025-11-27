// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    FString LogMessage = FString::Printf(TEXT("Initialized"));
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, LogMessage);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
}

void UQuestSubsystem::AddQuest(FActiveQuest NewQuest)
{
    ActiveQuests.Add(NewQuest);
    OnQuestUpdated.Broadcast();
}

void UQuestSubsystem::AddQuestFromAsset(UQuestDataAsset* QuestAsset)
{
    if (QuestAsset == nullptr) return;

    FActiveQuest NewQuestInstance = QuestAsset->QuestData;
    NewQuestInstance.bIsComplete = false;
    for (FQuestObjective& Objective : NewQuestInstance.Objectives)
    {
        Objective.CurrentCount = 0;
    }

    AddQuest(NewQuestInstance);
}

void UQuestSubsystem::UpdateObjectiveProgress(FName ObjectiveTag, int32 AmountToAdd)
{
    if (ObjectiveTag == NAME_None) return;

    bool bNeedsBroadcast = false;

    // On boucle sur NOS propres ActiveQuests (plus besoin de chercher le component)
    for (int32 i = ActiveQuests.Num() - 1; i >= 0; --i)
    {
        FActiveQuest& Quest = ActiveQuests[i];
        if (Quest.bIsComplete) continue;

        for (FQuestObjective& Objective : Quest.Objectives)
        {
            if (Objective.ObjectiveTag != ObjectiveTag) continue;
            if (Objective.CurrentCount >= Objective.TargetCount) continue;

            Objective.CurrentCount = FMath::Min(Objective.CurrentCount + AmountToAdd, Objective.TargetCount);
            bNeedsBroadcast = true;

            if (Objective.CurrentCount == Objective.TargetCount)
            {
                bool bAllObjectivesDone = true;
                for (const FQuestObjective& Obj : Quest.Objectives)
                {
                    if (Obj.CurrentCount < Obj.TargetCount)
                    {
                        bAllObjectivesDone = false;
                        break;
                    }
                }

                if (bAllObjectivesDone)
                {
                    Quest.bIsComplete = true;
                    GrantQuestRewards(Quest);
                    CompletedQuests.Add(Quest);
                    ActiveQuests.RemoveAt(i);
                }
            }
        }
    }

    if (bNeedsBroadcast)
    {
        OnQuestUpdated.Broadcast();
    }
}

void UQuestSubsystem::GrantQuestRewards(const FActiveQuest& Quest)
{
    // Ici, on a encore besoin de trouver le joueur pour lui donner la récompense (stats, xp...)
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
    if (PlayerCharacter)
    {
        for (UQuestReward* Reward : Quest.Rewards)
        {
            if (Reward)
            {
                Reward->ApplyReward(PlayerCharacter);
            }
        }
    }
}

void UQuestSubsystem::EnemyDied() 
{
    // On met à jour la quête via UpdateObjectiveProgress
    UpdateObjectiveProgress(FName("TuerEnnemi"), 1);
}

void UQuestSubsystem::ZoneCaptured() 
{
    // On envoie le Tag. Le "Count" est 1 (pour "1 fois 5 secondes")
    UpdateObjectiveProgress(FName("StayZone"), 1);
}

void UQuestSubsystem::PickedUp() 
{
    // On met à jour la quête
    UpdateObjectiveProgress(FName("CollectSphere"), 1);
}