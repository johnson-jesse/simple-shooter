// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	const TSubclassOf<class UUserWidget> ScreenClass = bIsWinner ? WinScreenClass : LoseScreenClass;
	if (UUserWidget* Screen = CreateWidget(this, ScreenClass); Screen != nullptr) Screen->AddToViewport();

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
