// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUDWidget.h"
#include "BaseCharacter.h"
#include "WaveGameMode.h"
#include "WaveManager.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

float UInGameHUDWidget::GetPlayerHealthPercent() const
{
	if (ABaseCharacter* P = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		if (P->MaxHealth > 0.f)
		{
			return FMath::Clamp(P->CurrentHealth / P->MaxHealth, 0.f, 1.f);
		}
	}
	return 0.f;
}

int32 UInGameHUDWidget::GetCurrentWave() const
{
	if (AWaveGameMode* GM = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (AWaveManager* WM = GM->GetWaveManager())
		{
			return WM->GetCurrentWaveNumber();
		}
	}
	return 0;
}

int32 UInGameHUDWidget::GetTotalWaves() const
{
	if (AWaveGameMode* GM = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (AWaveManager* WM = GM->GetWaveManager())
		{
			return WM->GetTotalWaves();
		}
	}
	return 0;
}

void UInGameHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (HealthBar)
	{
		HealthBar->SetPercent(GetPlayerHealthPercent());
	}
	if (WaveText)
	{
		const int32 W = GetCurrentWave();
		const int32 T = GetTotalWaves();
		WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave %d / %d"), W, T)));
	}
}
