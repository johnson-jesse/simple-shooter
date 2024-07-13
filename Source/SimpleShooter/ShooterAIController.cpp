// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	AShooterCharacter* AI = Cast<AShooterCharacter>(GetPawn());
	
	if (!AI->IsDead())
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
		GetBlackboardComponent()->ClearValue(TEXT("LastKnownPlayerLocation"));
		return;
	}
	
	if (LineOfSightTo(Player)) {
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), Player->GetActorLocation());
	}
	else GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
