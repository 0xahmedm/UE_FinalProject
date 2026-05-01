// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class FINALPROJECT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Game level to open when the user starts a new game
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	FName GameLevelName = TEXT("Lvl_ThirdPerson");

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void NewGame();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* NewGameButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* QuitButton;
};
