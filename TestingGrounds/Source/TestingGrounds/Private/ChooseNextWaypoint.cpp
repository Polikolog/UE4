// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto IndexQ = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);
	UE_LOG(LogTemp, Warning, TEXT("Index: %i"), IndexQ)
	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::GetPatrolPoints(UObject* Person)
{
	
}
