// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestPickup.h"
#include "Components/SphereComponent.h"      
#include "Components/StaticMeshComponent.h"  
#include "ProjetB3Character.h"               
#include "QuestComponent.h"                  

// Sets default values
AQuestPickup::AQuestPickup()
{
    // On n'a pas besoin d'appeler a chaque tick
    PrimaryActorTick.bCanEverTick = false;

    // --- Création de la Sphère ---
    OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
    SetRootComponent(OverlapSphere);           // La sphère est la base de l'objet
    OverlapSphere->InitSphereRadius(100.0f);   // Taille de la zone de détection
    OverlapSphere->SetCollisionProfileName(TEXT("Trigger")); // Mode "Déclencheur" (traverse mais détecte)

    // --- Création du Visuel ---
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(OverlapSphere); // On colle le visuel à la sphère
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Le visuel n'a pas de physique

    // --- Configuration par défaut ---
    // Le tag par défaut
    ObjectiveTag = FName("CollectSphere"); 

    // --- Abonnement à l'événement ---
    OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AQuestPickup::OnOverlapBegin);

}

void AQuestPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // A. Est-ce que c'est le joueur qui a touché la sphère ?
    AProjetB3Character* Player = Cast<AProjetB3Character>(OtherActor);

    if (Player)
    {
        // B. Est-ce que le joueur a un composant de quête ?
        UQuestComponent* QuestComp = Player->FindComponentByClass<UQuestComponent>();

        if (QuestComp)
        {
            // C. Mettre à jour la quête ! (Ajoute 1 au compteur)
            QuestComp->UpdateObjectiveProgress(ObjectiveTag, 1);

            // D. Détruire l'objet (puisqu'il est ramassé)
            Destroy();
        }
    }
}
