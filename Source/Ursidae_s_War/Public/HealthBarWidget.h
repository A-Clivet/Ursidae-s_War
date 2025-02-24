#pragma once

#include "CoreMinimal.h"
#include "Ours.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class URSIDAE_S_WAR_API UHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Fonction pour mettre à jour la barre de vie et le texte
    UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealthBar(float CurrentHealth, float MaxHealth);

protected:
    // Références aux widgets (Progress Bar et Texte)
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HealthText;
};
