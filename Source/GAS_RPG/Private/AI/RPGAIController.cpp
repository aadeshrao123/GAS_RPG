// Copyright AadeshRao


#include "AI/RPGAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ARPGAIController::ARPGAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard Component");
	check(Blackboard);

	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behaviour Tree Component");
	check(BehaviourTreeComponent);
}
