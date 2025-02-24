// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharactersBase.h"
#include "Components/SphereComponent.h"
#include "Ours.generated.h"

/**
 * Classe pour gérer les ours ennemis.
 */
UCLASS()
class URSIDAE_S_WAR_API AOurs : public ACharactersBase
{
	GENERATED_BODY()

public:
	// Constructeur
	AOurs();

	// Fonction appelée à chaque tick
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
	// Collision pour les interactions (ne jamais utiliser les sphere bizarre !!)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* DetectionBox;

	void UpdateHealthBar();

	


private:
	// Mesh représentant l'ours
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* OursMesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	// Widget
	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HealthBarWidgetComponent;

protected:
	// Définir les statistiques spécifiques à cet ours
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FCharactersStats OursStats;

};
