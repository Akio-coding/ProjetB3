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

    // Boucle sur toutes nos quêtes actives
    for (FActiveQuest& Quest : ActiveQuests)
    {
        // Si la quête est déjà complétée, on passe à la suivante
        if (Quest.bIsComplete) continue;

        // Boucle sur tous les objectifs de cette quête
        for (FQuestObjective& Objective : Quest.Objectives)
        {
            // On a trouvé le bon objectif !
            if (Objective.ObjectiveTag != ObjectiveTag) continue;
            
            //On vérifie s'il n'est pas déjà complété
            if (Objective.CurrentCount > Objective.TargetCount) continue;
            
            // Ajoute la progression
            Objective.CurrentCount = FMath::Min(Objective.CurrentCount + AmountToAdd, Objective.TargetCount);
            bNeedsBroadcast = true;

            // L'objectif est-il complet ? Si oui, vérifions la quête.
            if (Objective.CurrentCount == Objective.TargetCount)
            {
                bool bAllObjectivesDone = true;
                // On vérifie TOUS les autres objectifs de cette quête
                for (const FQuestObjective& Obj : Quest.Objectives)
                {
                    if (Obj.CurrentCount < Obj.TargetCount)
                    {
                        bAllObjectivesDone = false; // Un objectif n'est pas fini
                        break;
                    }
                }

                // Si TOUS les objectifs sont finis
                if (bAllObjectivesDone)
                {
                    Quest.bIsComplete = true; // Marque la quête
                    GrantQuestRewards(Quest); // Donne les récompenses !

                    // A ce stade, vous pourriez aussi supprimer la quête
                    // de la liste, ou la déplacer vers un TArray "CompletedQuests"
                }
            }

            ///envoyer un signal à l'objectif qui vient d'être mis à jour !
            // OnQuestUpdated.Broadcast(Objective);

            // // On peut s'arrêter ici car l'objectif est mis à jour
            // return;
            
        }
    }

    if (bNeedsBroadcast)
    {
        OnQuestUpdated.Broadcast(); // Notre nouveau signal simple !
    }
}