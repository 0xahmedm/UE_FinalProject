// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class FINALPROJECT_API UInGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "HUD")
	float GetPlayerHealthPercent() const;

	UFUNCTION(BlueprintPure, Category = "HUD")
	int32 GetCurrentWave() const;

	UFUNCTION(BlueprintPure, Category = "HUD")
	int32 GetTotalWaves() const;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* WaveText;
};
