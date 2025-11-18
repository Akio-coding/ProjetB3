// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProjetB3Character.h" 
#include "QuestComponent.h" 

// Sets default values
AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = false;
    bHasBeenTriggered = false;

    // 1. Initialiser la boîte d'overlap
    OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
    SetRootComponent(OverlapBox); // La boîte est la racine de l'acteur
    OverlapBox->SetCollisionProfileName(TEXT("Trigger")); // Réglé sur "Trigger"

    // 2. Initialiser le maillage (le cube visuel)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(OverlapBox); // Attaché à la boîte
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Pas de collision 

    // 3. Définir un tag par défaut
    ObjectiveTagToUpdate = FName(TEXT("TuerEnnemi"));

    // 4. Lier notre fonction à l'événement d'overlap
    OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}


void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Si déjà déclenché, ou si ce n'est pas le joueur, on sort
    if (bHasBeenTriggered || !OtherActor) return;

    // 1. Vérifier si c'est bien le joueur
    AProjetB3Character* PlayerCharacter = Cast<AProjetB3Character>(OtherActor);
    if (PlayerCharacter)
    {
        // 2. Récupérer le composant de quête du joueur
        UQuestComponent* QuestComp = PlayerCharacter->FindComponentByClass<UQuestComponent>();

        if (QuestComp)
        {
            // 3. Envoyer le signal de progression !
            QuestComp->UpdateObjectiveProgress(ObjectiveTagToUpdate, 1);

            // 4. On s'assure que ça n'arrive qu'une fois
            bHasBeenTriggered = true;

            // 5. Simuler la "mort" : l'acteur disparaît
            Destroy();
        }
    }
}
