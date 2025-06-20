// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FVEnemyAIController.generated.h"

class AFVPlayerBase;
class FObjectInitializer;
/**
 * 
 */
UCLASS()
class FALLINGVOID_API AFVEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit AFVEnemyAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = "Condition")
	FBlackboardKeySelector PlayerKey;

	/* Functions that might be used multiple times */

	/**
	 * @brief:  Sets the IsStunned key to the blackboard if it exist.
	 *			Makes the enemy no longer move and attack.
	 *			They still will know the player location.
	 */
	void SetIsStunned(bool value);

	/**
	 *  @brief : Sets the IsDead key in the blackboard to true if the enemy is dead. Only used for the boss.
	 */
	void SetIsDead(bool value);

	/**
	 * @brief Gets the closet player to this Mesh
	 */
	AFVPlayerBase* GetClosetPlayer() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
private:
};
