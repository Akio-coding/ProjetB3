// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestReward.h"
#include "Reward_IncreaseStat.generated.h"

/**
 * Une récompense qui applique une augmentation de stat (placeholder)
 */
UCLASS()
class PROJETB3_API UReward_IncreaseStat : public UQuestReward
{
	GENERATED_BODY()
	
public:
    // Override de la fonction de QuestReward
    virtual void ApplyReward_Implementation(ACharacter* PlayerCharacter) override;

    // --- Nos données spécifiques pour cette récompense ---

    // Le nom de la stat à augmenter (ex: "Sante", "Endurance")
    UPROPERTY(EditAnywhere, Category = "Reward")
    FName StatName;

    // Le montant de l'augmentation
    UPROPERTY(EditAnywhere, Category = "Reward")
    float Amount;
};
