// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "QuestData.h"
#include "QuestDataAsset.h"
#include "QuestSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestUpdated);

UCLASS()
class PROJETB3_API UQuestSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// --- Données
	// La liste des quêtes que le joueur a actuellement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FActiveQuest> ActiveQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FActiveQuest> CompletedQuests;

	// Le "signal" de mise à jour pour l'UI
	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestUpdated OnQuestUpdated;

public : 
	// --- Fonctions
	// Fonction pour ajouter une nouvelle quête
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuest(FActiveQuest NewQuest);

	// Ajout de quête avec data asset
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void AddQuestFromAsset(UQuestDataAsset* QuestAsset);

	// Appelée par d'autres objets (ex: un ennemi qui meurt) pour faire progresser un objectif
	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateObjectiveProgress(FName ObjectiveTag, int32 AmountToAdd = 1);

	UFUNCTION()
	void EnemyDied();

	UFUNCTION()
	void ZoneCaptured();

	UFUNCTION()
	void PickedUp();

protected :
	// Fonction pour donner les récompenses
	void GrantQuestRewards(const FActiveQuest& Quest);
};

