// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestZone.generated.h"

UCLASS()
class PROJETB3_API AQuestZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestZone();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* OverlapBox;

    // Le tag de la quête à mettre à jour
    UPROPERTY(EditAnywhere, Category = "Quest")
    FName ObjectiveTag;

    // Le temps en secondes requis dans la zone
    UPROPERTY(EditAnywhere, Category = "Quest")
    float TimeRequired = 5.0f;

    // --- Variables de suivi ---
    // Le temps actuel accumulé
    float AccumulatedTime = 0.0f;

    // Le joueur est-il dans la zone ?
    bool bIsPlayerInside = false;

    // La quête a-t-elle déjà été validée ?
    bool bHasBeenCompleted = false;

    // Référence au joueur 
    UPROPERTY()
    class AProjetB3Character* PlayerRef;

    // Fonctions d'Overlap
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
        class AActor* OtherActor, 
        class UPrimitiveComponent* OtherComp, 
        int32 OtherBodyIndex, 
        bool bFromSweep, 
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, 
        class AActor* OtherActor, 
        class UPrimitiveComponent* OtherComp, 
        int32 OtherBodyIndex);

    virtual void Tick(float DeltaTime) override;

};
