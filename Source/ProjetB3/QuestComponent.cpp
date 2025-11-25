// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "QuestDataAsset.h"
#include "GameFramework/Character.h"

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
    OnQuestUpdated.Broadcast();
}

void UQuestComponent::AddQuestFromAsset(UQuestDataAsset* QuestAsset)
{
    if (QuestAsset == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("AddQuestFromAsset: QuestAsset était null !"));
        return;
    }

    // 1. On COPIE les données du Data Asset dans une nouvelle instance
    FActiveQuest NewQuestInstance = QuestAsset->QuestData;

    // 2. IMPORTANT : On réinitialise les valeurs de progression !
    // (Sinon, la quête pourrait démarrer comme "complète" si cochée
    // accidentellement dans le Data Asset)
    NewQuestInstance.bIsComplete = false;
    for (FQuestObjective& Objective : NewQuestInstance.Objectives)
    {
        Objective.CurrentCount = 0;
    }

    // 3. On appelle notre fonction de base pour ajouter l'instance
    AddQuest(NewQuestInstance);
}



// Fonction pour donner les récompenses
void UQuestComponent::GrantQuestRewards(const FActiveQuest& Quest)
{
    // Nous devons trouver le joueur auquel ce composant est attaché
    ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
    if (PlayerCharacter == nullptr) return;

    // C'est la magie du polymorphisme !
    // Nous appelons "ApplyReward" sans savoir ce que c'est.
    for (UQuestReward* Reward : Quest.Rewards)
    {
        if (Reward)
        {
            Reward->ApplyReward(PlayerCharacter);
        }
    }
}

void UQuestComponent::UpdateObjectiveProgress(FName ObjectiveTag, int32 AmountToAdd)
{
    if (ObjectiveTag == NAME_None) return; // Ne fait rien si le Tag est invalide

    bool bNeedsBroadcast = false;

    // CHANGEMENT : On boucle à l'envers (int32 i = Num() - 1; i >= 0; --i)
    // Cela nous permet de supprimer des éléments (RemoveAt) sans casser la boucle.
    for (int32 i = ActiveQuests.Num() - 1; i >= 0; --i)
    {
        // On récupère une référence à la quête via son index
        FActiveQuest& Quest = ActiveQuests[i];

        if (Quest.bIsComplete) continue;

        for (FQuestObjective& Objective : Quest.Objectives)
        {
            if (Objective.ObjectiveTag != ObjectiveTag) continue;
            if (Objective.CurrentCount >= Objective.TargetCount) continue; // Correction: >= au lieu de >

            // Ajoute la progression
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

                    // --- C'EST ICI QUE LA MAGIE OPÈRE ---
                    // 1. On archive la quête dans la liste des terminées
                    CompletedQuests.Add(Quest);

                    // 2. On la supprime de la liste active
                    // L'UI, qui lit "ActiveQuests", ne la verra plus !
                    ActiveQuests.RemoveAt(i);
                }
            }
        }
    }

    if (bNeedsBroadcast)
    {
        OnQuestUpdated.Broadcast(); // Envoi du signal 
    }



    //// Boucle sur toutes nos quêtes actives
    //for (FActiveQuest& Quest : ActiveQuests)
    //{
    //    // Si la quête est déjà complétée, on passe à la suivante
    //    if (Quest.bIsComplete) continue;

    //    // Boucle sur tous les objectifs de cette quête
    //    for (FQuestObjective& Objective : Quest.Objectives)
    //    {
    //        // On a trouvé le bon objectif !
    //        if (Objective.ObjectiveTag != ObjectiveTag) continue;
    //        
    //        //On vérifie s'il n'est pas déjà complété
    //        if (Objective.CurrentCount > Objective.TargetCount) continue;
    //        
    //        // Ajoute la progression
    //        Objective.CurrentCount = FMath::Min(Objective.CurrentCount + AmountToAdd, Objective.TargetCount);
    //        bNeedsBroadcast = true;

    //        // L'objectif est-il complet ? Si oui, on vérifie la quête.
    //        if (Objective.CurrentCount == Objective.TargetCount)
    //        {
    //            bool bAllObjectivesDone = true;
    //            // On vérifie TOUS les autres objectifs de cette quête
    //            for (const FQuestObjective& Obj : Quest.Objectives)
    //            {
    //                if (Obj.CurrentCount < Obj.TargetCount)
    //                {
    //                    bAllObjectivesDone = false; // Un objectif n'est pas fini
    //                    break;
    //                }
    //            }

    //            // Si TOUS les objectifs sont finis
    //            if (bAllObjectivesDone)
    //            {
    //                Quest.bIsComplete = true; // Marque la quête
    //                GrantQuestRewards(Quest); // Donne les récompenses ! 
    //            }
    //        }
    //    }
    //}
}