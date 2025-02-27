// Copyright: Falling Void Studios


#include "FVBTWait.h"

#include "BehaviorTree/BlackboardComponent.h"

UFVBTWait::UFVBTWait()
{
	NodeName = TEXT("Wait");
	m_RemainingWaitTime = 0.0f;
}

EBTNodeResult::Type UFVBTWait::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (WaitDurationKey.IsSet())
	{
		m_RemainingWaitTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(WaitDurationKey.SelectedKeyName);
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	if (m_RemainingWaitTime > 0.0f)
	{
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Succeeded;
}

void UFVBTWait::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	m_RemainingWaitTime -= DeltaSeconds;

	if (m_RemainingWaitTime <= 0.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
