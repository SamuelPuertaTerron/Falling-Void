// Copyright: Falling Void Studios


#include "Enemy AI/FVBTRandomSelector.h"

UFVBTRandomSelector::UFVBTRandomSelector()
{
    NodeName = "Random Selector";
}

int32 UFVBTRandomSelector::GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
    if (LastResult == EBTNodeResult::Succeeded)
    {
        return BTSpecialChild::ReturnToParent;
    }
<<<<<<< Updated upstream

    const int32 NextChildIdx = FMath::RandRange(0, GetChildrenNum() - 1);
    return NextChildIdx;
=======
    // Generate new random index when:
    // - First execution (PrevChild == -1)
    // - Previous child finished (success/failure)
    const int32 NextChild = (PrevChild == -1 || LastResult != EBTNodeResult::InProgress)
        ? FMath::RandRange(0, GetChildrenNum() - 1)
        : PrevChild;

    return NextChild;
>>>>>>> Stashed changes
}
