// Copyright: Falling Void Studios


#include "Enemy AI/FVBTCheckAttackCooldown.h"

#include "FVEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/FVEnemyBase.h"

UFVBTCheckAttackCooldown::UFVBTCheckAttackCooldown()
{
	NodeName = "Attack Cooldown";
}

bool UFVBTCheckAttackCooldown::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AFVEnemyAIController* controller = Cast<AFVEnemyAIController>(OwnerComp.GetAIOwner());
    if (!controller)
    {
        return false;
    }

    AFVEnemyBase* enemy = Cast<AFVEnemyBase>(controller->GetPawn());
    if (!enemy)
    {
        return false;
    }

    float lastAttackTime = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(LastAttackTIme.SelectedKeyName); //TODO: Add error checking for BB components. 
    float currentTime = GetWorld()->GetTimeSeconds();

    // If never attacked or cooldown has passed
    if (lastAttackTime <= 0.f || (currentTime - lastAttackTime) >= enemy->AttackTime)
    {
        return true;
    }

    return false;
}
