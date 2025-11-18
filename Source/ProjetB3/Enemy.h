// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class PROJETB3_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* OverlapBox;

    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UStaticMeshComponent* MeshComponent;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
        class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    // Le Tag d'objectif que cet ennemi fait progresser en mourant
    UPROPERTY(EditAnywhere, Category = "Quest")
    FName ObjectiveTagToUpdate;

    // Pour s'assurer qu'on ne le "tue" qu'une seule fois
    bool bHasBeenTriggered;

};
