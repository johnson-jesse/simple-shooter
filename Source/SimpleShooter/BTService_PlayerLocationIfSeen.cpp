// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"

#include "ShooterCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location LoS");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (OwnerComp.GetAIOwner() == nullptr) return;

	AShooterCharacter* Shooter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Shooter == nullptr) return;

	const APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (OwnerComp.GetAIOwner()->LineOfSightTo(Player))
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	else OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}
