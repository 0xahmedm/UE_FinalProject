// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;

UCLASS()
class FINALPROJECT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	FName MainMenuLevelName = TEXT("Lvl_MainMenu");

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void Resume();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void QuitGame();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* QuitButton;
};
