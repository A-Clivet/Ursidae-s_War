// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharactersBase.generated.h"

// Structure pour regrouper les statistiques
USTRUCT(BlueprintType)
struct FCharactersStats
{
    GENERATED_BODY()

    // Constructeur par défaut pour initialiser les valeurs
    FCharactersStats()
        : Level(1),
          Health(10),
          MaxHealth(10),
          MoveSpeed(5), // en m/s
          AtkSpeed(1.0f), // en attaque par seconde
          StatsPoints(0),
          Attack(3),
          Experience(0),
          ExpLimit(300) // Première limite d'expérience de EXPLimits
    {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float AtkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int StatsPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int Experience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int ExpLimit;
};

UCLASS()
class URSIDAE_S_WAR_API ACharactersBase : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACharactersBase();

protected:
    // Appelé au début du jeu ou au spawn
    virtual void BeginPlay() override;

public:
    // Appelé à chaque frame
    virtual void Tick(float DeltaTime) override;

    // Appelé pour lier des actions ou axes d'input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // --- Fonctionnalités principales ---
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void TakeDamage(int Damage);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void OnDeath();
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void GainExperience(int ExpGained);
    
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Attack();
    
    // UFUNCTION(BlueprintCallable, Category = "Combat")
    // void OnTriggerStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    //     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void InflictDamage(ACharactersBase* Target);



protected:
    // --- Stats ---
    
    // Propriétés des statistiques du personnage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowProtectedAccess = "true"))
    FCharactersStats Stats;

    // Tableaux des limites d'expérience et des points de statistiques par niveau
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowProtectedAccess = "true"))
    TArray<int> EXPLimits = {300, 450, 675, 1050, 1575, 2400, 3600, 5400, 8100};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowProtectedAccess = "true"))
    TArray<int> StatPointsEnum = {0, 3, 2, 3, 4, 6, 9, 13, 20, 30};
};
