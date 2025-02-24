#include "Ours.h"

#include "HealthBarWidget.h"
#include "Panda.h"
#include "CharactersBase.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Constructeur
AOurs::AOurs()
{
	PrimaryActorTick.bCanEverTick = true;

	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(RootComponent);
	DetectionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f)); // Taille de la box
	DetectionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionBox->SetCollisionObjectType(ECC_WorldDynamic);
	DetectionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	DetectionBox->SetGenerateOverlapEvents(true);
	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &AOurs::OnOverlapBegin);
	DetectionBox->SetHiddenInGame(false);
	DetectionBox->SetVisibility(true);



	// Créer et attacher le Static Mesh
	OursMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OursMesh"));
	OursMesh->SetupAttachment(RootComponent);

	if (!DetectionBox->OnComponentBeginOverlap.IsAlreadyBound(this, &AOurs::OnOverlapBegin))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin not bound! Binding now."));
		DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &AOurs::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin already bound."));
	}


	// Ajouter le composant Widget
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);

	
	HealthBarWidgetComponent->SetWidgetClass(UHealthBarWidget::StaticClass());

	// Configurer le widget
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	HealthBarWidgetComponent->SetDrawSize(FVector2D(150.f, 50.f)); // Taille du widget


	
}

void AOurs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AOurs::BeginPlay()
{
	Super::BeginPlay();

	UpdateHealthBar();

	DrawDebugBox(GetWorld(), HealthBarWidgetComponent->GetComponentLocation(), FVector(50, 50, 50), FColor::Red, true, 5.0f);

}


void AOurs::UpdateHealthBar()
{
	if (UHealthBarWidget* HealthBar = Cast<UHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		HealthBar->UpdateHealthBar( OursStats.Health, OursStats.MaxHealth);
	}
}

void AOurs::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                           bool bFromSweep, const FHitResult& SweepResult)
{
	// Affiche les informations de l'acteur détecté
	UE_LOG(LogTemp, Warning, TEXT("Detected overlap with actor: %s"), *OtherActor->GetName());

	// Vérifie si l'acteur détecté est de type APanda
	if (OtherActor->IsA(APanda::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap with Panda detected."));
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
											 FString::Printf(TEXT("Overlapping with Panda: %s"), *OtherActor->GetName()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap with non-panda actor: %s"), *OtherActor->GetName());
	}
}

