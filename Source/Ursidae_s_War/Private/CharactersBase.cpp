#include "CharactersBase.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"

// Constructeur
ACharactersBase::ACharactersBase()
{
    PrimaryActorTick.bCanEverTick = true; // Autorise la mise à jour chaque frame

}

// Appelé au début
void ACharactersBase::BeginPlay()
{
    Super::BeginPlay();
}

// Appelé chaque frame
void ACharactersBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Configurer les inputs du joueur
void ACharactersBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// --- Fonctions principales ---

void ACharactersBase::TakeDamage(int Damage)
{
    Stats.Health -= Damage;

    if (Stats.Health <= 0)
    {
        OnDeath();
    }
}


void ACharactersBase::OnDeath() // peut metre le character touches en parametre
{
    AActor* LastAttacker = nullptr; // Remplacez par la logique pour récupérer l'attaquant

    if (LastAttacker)
    {
        ACharactersBase* Attacker = Cast<ACharactersBase>(LastAttacker);
        if (Attacker)
        {
            Attacker->GainExperience(Stats.Experience);
        }
    }

    Destroy();
}

void ACharactersBase::Attack()
{
    UE_LOG(LogTemp, Warning, TEXT("Attaque lancée !"));
}


void ACharactersBase::GainExperience(int ExpGained)
{
    Stats.Experience += ExpGained;
//-----------------------------------------------------------------------------------------------   modifier les valeurs
    // Exemple de limite pour le niveau
    if (Stats.Experience >= Stats.ExpLimit)
    {
        Stats.Experience -= Stats.ExpLimit;
        Stats.StatsPoints += StatPointsEnum[Stats.Level];
        Stats.ExpLimit += EXPLimits[Stats.Level];
        Stats.Level++;
    }
}


void ACharactersBase::InflictDamage(ACharactersBase* Target)
{
    if (Target)
    {
        Target->TakeDamage(Stats.Attack);
    }
}

// // pas sur si encore necessaire
// void ACharactersBase::OnTriggerStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
//     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
//     if (!OtherActor || OtherActor == this)
//     {
//         return;
//     }
//
//     if (OtherActor->ActorHasTag("Enemy"))
//     {
//         InflictDamage(Cast<ACharactersBase>(OtherActor));
//     }
//
//     if (OtherActor->ActorHasTag("Player"))
//     {
//         InflictDamage(Cast<ACharactersBase>(this));
//     }
// }
