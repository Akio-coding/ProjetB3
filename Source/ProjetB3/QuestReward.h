// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestReward.generated.h"

class ACharacter;

/**
 * Classe de base abstraite pour toute récompense de quête.
 * Ne peut pas être utilisée directement, doit être héritée.
 */

UCLASS(Abstract, Blueprintable, EditInlineNew)
class PROJETB3_API UQuestReward : public UObject
{
	GENERATED_BODY()
	
public:
    // La fonction que toutes les récompenses doivent implémenter
    // 'BlueprintNativeEvent' signifie qu'elle peut être codée en C++ (Implementation)
    // ou entièrement en Blueprint.
    UFUNCTION(BlueprintNativeEvent, Category = "Quest Reward")
    void ApplyReward(ACharacter* PlayerCharacter);

    // Fonction C++ de base
    virtual void ApplyReward_Implementation(ACharacter* PlayerCharacter);
};
