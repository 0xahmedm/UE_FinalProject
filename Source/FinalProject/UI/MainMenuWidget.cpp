// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (NewGameButton) NewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGame);
	if (QuitButton)    QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
}

void UMainMenuWidget::NewGame()
{
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
