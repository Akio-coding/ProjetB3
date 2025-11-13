// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLogWidget.h"

#include "Kismet/GameplayStatics.h"
#include "QuestComponent.h" // N'oubliez pas d'inclure le composant
#include "GameFramework/Pawn.h" // Pour trouver notre joueur

void UQuestLogWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Trouvons le "Pawn" (personnage) du joueur
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (PlayerPawn)
    {
        // Trouvons le composant de quête sur ce joueur
        QuestComponent = PlayerPawn->FindComponentByClass<UQuestComponent>();
        if (QuestComponent)
        {
            // C'est l'étape cruciale : nous "abonnons" notre widget
            // au signal "OnQuestUpdated" du composant.
            QuestComponent->OnQuestUpdated.AddDynamic(this, &UQuestLogWidget::HandleQuestUpdated);

            // Appelons-le une fois au début pour afficher les quêtes actuelles
            HandleQuestUpdated(FQuestObjective());
        }
    }
}

void UQuestLogWidget::HandleQuestUpdated(const FQuestObjective& QuestData)
{
    // Quand le composant émet le signal, cette fonction est appelée.
    // Elle ne fait qu'une chose : appeler l'événement Blueprint
    // pour que l'éditeur puisse s'occuper de l'affichage.
    OnQuestDataUpdated(QuestData);
}