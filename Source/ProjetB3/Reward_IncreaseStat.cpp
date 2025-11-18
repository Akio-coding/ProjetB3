// Fill out your copyright notice in the Description page of Project Settings.


#include "Reward_IncreaseStat.h"

void UReward_IncreaseStat::ApplyReward_Implementation(ACharacter* PlayerCharacter)
{

    if (PlayerCharacter == nullptr) return;

    // --- LOGIQUE DE RÉCOMPENSE ---
    // Pour l'instant, il n'y a pas de système de stats,
    // donc afficher un message de log à la place.

    // Système de stats à mettre ici.

    FString LogMessage = FString::Printf(
        TEXT("Récompense de quête appliquée : Augmentation de la stat '%s' de %.1f"),
        *StatName.ToString(),
        Amount
    );

    // Affiche le message en jaune sur l'écran (pour le debug)
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, LogMessage);

    // Affiche aussi dans la console de log
    UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
}