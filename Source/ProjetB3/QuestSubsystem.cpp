// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "QuestComponent.h"

void UQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
    FString LogMessage = FString::Printf(TEXT("Initialized"));
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, LogMessage);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
}

void UQuestSubsystem::EnemyDied() 
{
    // 1. Trouver le joueur (PlayerCharacter)
    // Le Subsystem vit dans le monde, il peut accéder au contexte du monde
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
    if (PlayerCharacter)
    {
        // 2. Trouver son QuestComponent
        UQuestComponent* QuestComp = PlayerCharacter->FindComponentByClass<UQuestComponent>();
        if (QuestComp)
        {
            FName TagParDefaut = FName("TuerEnnemi");
            // 3. Mettre à jour la quête
            QuestComp->UpdateObjectiveProgress(TagParDefaut,1);
        }
    }
}