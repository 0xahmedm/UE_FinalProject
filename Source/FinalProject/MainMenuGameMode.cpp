// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC || !MainMenuWidgetClass) return;

	MainMenuWidget = CreateWidget<UUserWidget>(PC, MainMenuWidgetClass);
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport(0);
		PC->SetShowMouseCursor(true);
		FInputModeUIOnly Mode;
		PC->SetInputMode(Mode);
	}
}
