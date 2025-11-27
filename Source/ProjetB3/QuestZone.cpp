// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestZone.h"
#include "Components/BoxComponent.h"
#include "ProjetB3Character.h"  
#include "QuestSubsystem.h"

// Sets default values
AQuestZone::AQuestZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
    SetRootComponent(OverlapBox);
    OverlapBox->SetCollisionProfileName(TEXT("Trigger"));

    // Lier les fonctions aux événements d'overlap
    OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AQuestZone::OnOverlapBegin);
    OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AQuestZone::OnOverlapEnd);
}

void AQuestZone::BeginPlay()
{
    Super::BeginPlay();
    UQuestSubsystem* QuestSubsystem = GetWorld()->GetSubsystem<UQuestSubsystem>();
    this->ZoneCaptured.AddDynamic(QuestSubsystem, &UQuestSubsystem::ZoneCaptured);
}

void AQuestZone::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    // Vérifier si c'est le joueur
    AProjetB3Character* Player = Cast<AProjetB3Character>(OtherActor);
    if (Player && !bHasBeenCompleted)
    {
        bIsPlayerInside = true;
        PlayerRef = Player; // Stocker la référence
    }
}

void AQuestZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex)
{
    // Si le joueur sort
    AProjetB3Character* Player = Cast<AProjetB3Character>(OtherActor);
    if (Player)
    {
        bIsPlayerInside = false;
        PlayerRef = nullptr;
    }
}

// Called every frame
void AQuestZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Si la quête est finie, on ne fait plus rien
    if (bHasBeenCompleted) return;

    // Si le joueur est dans la zone
    if (bIsPlayerInside && PlayerRef)
    {
        AccumulatedTime += DeltaTime; // Ajouter le temps écoulé

        // A-t-on atteint le temps requis ?
        if (AccumulatedTime >= TimeRequired)
        {
            bHasBeenCompleted = true; // Marquer comme terminé

            ZoneCaptured.Broadcast();
            
            // Désactivation du tick pour économiser les performances
            SetActorTickEnabled(false);
            Destroy(); 
        }
    }
}

