// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndScreenWidget.generated.h"

class UButton;

// Shared base used for both the Win and Lose screens
UCLASS()
class FINALPROJECT_API UEndScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	FName MainMenuLevelName = TEXT("Lvl_MainMenu");

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void Restart();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ReturnToMainMenu();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* MainMenuButton;
};
