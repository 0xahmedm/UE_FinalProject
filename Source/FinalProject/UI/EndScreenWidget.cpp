// Fill out your copyright notice in the Description page of Project Settings.

#include "EndScreenWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UEndScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (RestartButton)  RestartButton->OnClicked.AddDynamic(this, &UEndScreenWidget::Restart);
	if (MainMenuButton) MainMenuButton->OnClicked.AddDynamic(this, &UEndScreenWidget::ReturnToMainMenu);
}

void UEndScreenWidget::Restart()
{
	UGameplayStatics::SetGamePaused(this, false);
	const FName CurrentMap(*UGameplayStatics::GetCurrentLevelName(this, true));
	UGameplayStatics::OpenLevel(this, CurrentMap);
}

void UEndScreenWidget::ReturnToMainMenu()
{
	UGameplayStatics::SetGamePaused(this, false);
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}
