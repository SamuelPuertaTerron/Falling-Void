// Copyright: Falling Void Studios


#include "Enemy AI/FVBTEndRetreat.h"

#include "BehaviorTree/BlackboardComponent.h"

UFVBTEndRetreat::UFVBTEndRetreat()
{
	NodeName = "End Retreat";
}

EBTNodeResult::Type UFVBTEndRetreat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(RetreatKey.SelectedKeyName, false);

	return EBTNodeResult::Succeeded;
}