// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	// AShooterCharacter* AI = Cast<AShooterCharacter>(GetPawn());
	//
	// if (!AI->IsDead() && LineOfSightTo(Player))
	// {
	// 	SetFocus(Player);
	// 	MoveToActor(Player, 200);
	// }
	// else
	// {
	// 	ClearFocus(EAIFocusPriority::Gameplay);
	// 	StopMovement();
	// }
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
	}
}
