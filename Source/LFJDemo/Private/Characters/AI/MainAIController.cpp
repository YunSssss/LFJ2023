// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/MainAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI/MainAICharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"



AMainAIController::AMainAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponennt"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObj(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprints/Ai/BT_MainAI.BT_MainAI'"));
	if (BTObj.Succeeded())
	{
		BehaviorTree = BTObj.Object;
	}
}	

void AMainAIController::OnPossess(APawn* InPawn)
{
	AMainAICharacter* AIChar = Cast<AMainAICharacter>(InPawn);
	if (AIChar == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("OnPossess"));
	Super::OnPossess(InPawn);


	if (AIChar != nullptr && BehaviorTree != nullptr)
	{

		UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp);
		AIChar->BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}

	if (BehaviorTreeComp)
	{
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}
	
}

void AMainAIController::OnUnPossess()
{
	Super::OnUnPossess();

	if (BehaviorTreeComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnUnPossess"));
		BehaviorTreeComp->StopTree(EBTStopMode::Safe);
	}
}
