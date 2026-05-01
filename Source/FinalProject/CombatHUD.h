// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatHUD.generated.h"

class UUserWidget;

UCLASS()
class FINALPROJECT_API ACombatHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> InGameHUDClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> LoseScreenClass;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowInGameHUD();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HidePauseMenu();

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsPauseMenuShown() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void TogglePauseMenu();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowWinScreen();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowLoseScreen();

protected:
	virtual void BeginPlay() override;

	UPROPERTY() UUserWidget* InGameHUDWidget = nullptr;
	UPROPERTY() UUserWidget* PauseMenuWidget = nullptr;
	UPROPERTY() UUserWidget* EndScreenWidget = nullptr;
};
