#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(CurrentHealth / MaxHealth);
	}
	if (HealthText)
	{
		FString HealthString = FString::Printf(TEXT("%d/%d"), FMath::RoundToInt(CurrentHealth), FMath::RoundToInt(MaxHealth));
		HealthText->SetText(FText::FromString(HealthString));
	}
}
