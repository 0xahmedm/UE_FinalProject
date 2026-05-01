// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void ACombatHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowInGameHUD();
}

void ACombatHUD::ShowInGameHUD()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !InGameHUDClass) return;

	if (!InGameHUDWidget)
	{
		InGameHUDWidget = CreateWidget<UUserWidget>(PC, InGameHUDClass);
	}
	if (InGameHUDWidget && !InGameHUDWidget->IsInViewport())
	{
		InGameHUDWidget->AddToViewport(0);
	}

	// Reset input back to gameplay (LocalPlayer can carry UIOnly state across level loads)
	PC->SetShowMouseCursor(false);
	PC->SetInputMode(FInputModeGameOnly());
}

void ACombatHUD::ShowPauseMenu()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !PauseMenuClass) return;

	if (!PauseMenuWidget)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(PC, PauseMenuClass);
	}
	if (PauseMenuWidget && !PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->AddToViewport(10);
	}

	UGameplayStatics::SetGamePaused(this, true);
	PC->SetShowMouseCursor(true);

	FInputModeUIOnly Mode;
	if (PauseMenuWidget)
	{
		Mode.SetWidgetToFocus(PauseMenuWidget->TakeWidget());
	}
	PC->SetInputMode(Mode);
}

void ACombatHUD::HidePauseMenu()
{
	if (PauseMenuWidget && PauseMenuWidget->IsInViewport())
	{
		PauseMenuWidget->RemoveFromParent();
	}
	UGameplayStatics::SetGamePaused(this, false);
	if (APlayerController* PC = GetOwningPlayerController())
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
}

bool ACombatHUD::IsPauseMenuShown() const
{
	return PauseMenuWidget && PauseMenuWidget->IsInViewport();
}

void ACombatHUD::TogglePauseMenu()
{
	if (IsPauseMenuShown()) HidePauseMenu();
	else ShowPauseMenu();
}

void ACombatHUD::ShowWinScreen()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !WinScreenClass || EndScreenWidget) return;

	EndScreenWidget = CreateWidget<UUserWidget>(PC, WinScreenClass);
	if (EndScreenWidget)
	{
		EndScreenWidget->AddToViewport(20);
		PC->SetShowMouseCursor(true);
		FInputModeUIOnly Mode;
		PC->SetInputMode(Mode);
	}
}

void ACombatHUD::ShowLoseScreen()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC || !LoseScreenClass || EndScreenWidget) return;

	EndScreenWidget = CreateWidget<UUserWidget>(PC, LoseScreenClass);
	if (EndScreenWidget)
	{
		EndScreenWidget->AddToViewport(20);
		PC->SetShowMouseCursor(true);
		FInputModeUIOnly Mode;
		PC->SetInputMode(Mode);
	}
}
