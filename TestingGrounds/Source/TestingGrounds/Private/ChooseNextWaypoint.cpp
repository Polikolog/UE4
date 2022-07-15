// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto AIController = OwnerComp.GetAIOwner();
	auto ControllePawn = AIController->GetPawn();
	auto PatrolRouteComponent = ControllePawn->FindComponentByClass<UPatrolRouteComponent>();

	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; }

	auto IndexQ = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);
	auto Points = PatrolRouteComponent->GetPoints();

	if (ensure(Points.Num() < 1)) { return EBTNodeResult::Failed; }

	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, Points[IndexQ]);

	auto Procent = (IndexQ + 1) % Points.Num();

	BlackboardComp->SetValueAsInt(Index.SelectedKeyName, Procent);

	return EBTNodeResult::Succeeded;
}
