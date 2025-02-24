#include "Panda.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructeur
APanda::APanda()
{
	PrimaryActorTick.bCanEverTick = true;

	// Désactiver l'orientation automatique
	bUseControllerRotationYaw = false;

	// Assurez-vous que le Character Movement gère la rotation
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f); // Vitesse de rotation

	// Créer un Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent); // Attacher au personnage
	SpringArm->TargetArmLength = 800.0f;       // Distance de la caméra
	SpringArm->bEnableCameraLag = true;       // Lag de la caméra pour un effet plus fluide
	SpringArm->CameraLagSpeed = 3.0f;
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f)); // Angle de la caméra
	SpringArm->SetUsingAbsoluteRotation(true); // Assurez-vous que le SpringArm ne suit pas la rotation du personnage

	// Créer la caméra
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm); // Attacher à l'extrémité du Spring Arm

	// Créer et attacher le Static Mesh
	PandaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PandaMesh"));
	PandaMesh->SetupAttachment(RootComponent);
	PandaMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PandaMesh->SetCollisionObjectType(ECC_Pawn);
	PandaMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	PandaMesh->SetGenerateOverlapEvents(true);

}

// --------------------------- Fonctions ------------------------------------------

void APanda::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// Affiche le curseur de la souris
		PlayerController->bShowMouseCursor = true;

		// Autorise le clic dans le monde avec la souris
		PlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs; // Change l'icône si besoin
	}
}



void APanda::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Associer le clic droit à une fonction
	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &APanda::HandleRightClick);
}

void APanda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Déplacement progressif
	if (bHasDestination)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector Direction = TargetLocation - CurrentLocation;

		// Vérifie si le panda est proche de la cible avec une tolérance
		float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);
		if (DistanceToTarget <= AcceptanceRadius)
		{
			bHasDestination = false; // Arrêter le déplacement
			return; // Sortir pour éviter les calculs inutiles
		}

		// Neutraliser l'axe Z pour éviter l'inclinaison
		Direction.Z = 0;

		// Normaliser la direction
		if (!Direction.IsNearlyZero(0.1f)) // Seuil de 0.1 pour éviter des calculs inutiles sur des valeurs très petites
		{
			Direction.Normalize();

			// Ajouter le mouvement
			AddMovementInput(Direction);

			// Mettre à jour la rotation fluide
			FRotator TargetRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			TargetRotation.Pitch = 0; // Verrouiller l'axe vertical
			TargetRotation.Roll = 0;  // Verrouiller l'axe horizontal
			FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 10.0f);

			// Appliquer la rotation uniquement si le panda est en mouvement
			SetActorRotation(SmoothRotation);
		}
	}
}


void APanda::HandleRightClick()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController) return;

	FVector WorldLocation, WorldDirection;
	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.0f);

		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
		{
			TargetLocation = HitResult.Location;

			// Activer la destination pour que Tick prenne en charge la rotation fluide
			bHasDestination = true;
		}
	}
}
