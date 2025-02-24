#pragma once

#include "CoreMinimal.h"
#include "CharactersBase.h"
#include "Panda.generated.h"

/**
 * Classe pour gérer le personnage principal, le panda.
 */
UCLASS()
class URSIDAE_S_WAR_API APanda : public ACharactersBase
{
	GENERATED_BODY()

public:
	// Constructeur
	APanda();

	// Fonctions principales du cycle de vie
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Configuration des entrées du joueur
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Gestion du clic droit pour déplacer le panda
	void HandleRightClick();

protected:
	// Variables pour le déplacement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bHasDestination = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "10.0", ClampMax = "500.0"))
	float AcceptanceRadius = 100.0f; // Rayon de tolérance autour de la destination

private:
	// Spring Arm pour positionner la caméra
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	// Caméra principale attachée au Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	// Mesh représentant le panda
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PandaMesh;
};
