// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenuWidget.h"
#include "CombatHUD.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ResumeButton)   ResumeButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Resume);
	if (MainMenuButton) MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ReturnToMainMenu);
	if (QuitButton)     QuitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::QuitGame);
}

void UPauseMenuWidget::Resume()
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	if (ACombatHUD* HUD = Cast<ACombatHUD>(PC->GetHUD()))
	{
		HUD->HidePauseMenu();
	}
}

void UPauseMenuWidget::ReturnToMainMenu()
{
	UGameplayStatics::SetGamePaused(this, false);
	UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}

void UPauseMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
