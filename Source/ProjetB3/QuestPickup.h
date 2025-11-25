// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestPickup.generated.h"

UCLASS()
class PROJETB3_API AQuestPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestPickup();

protected:
    // 1. La sphère de détection (invisible) qui déclenche l'événement
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USphereComponent* OverlapSphere;

    // 2. Le visuel de l'objet
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    // 3. Le Tag de la quête
    UPROPERTY(EditAnywhere, Category = "Quest")
    FName ObjectiveTag;

    // 4. Fonction overlap
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
        class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
