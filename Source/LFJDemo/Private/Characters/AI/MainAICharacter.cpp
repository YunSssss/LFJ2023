// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/MainAICharacter.h"
#include "Characters/AI/MainAIController.h"

#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/AI/MainAIController.h"
#include "Characters/MainPlayerCharacter.h"

AMainAICharacter::AMainAICharacter()
{
	AIControllerClass = AMainAIController::StaticClass();

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AMainAICharacter::OnSeenPawn);
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

}

void AMainAICharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMainAICharacter::OnSeenPawn(APawn* Pawn)
{
	
	AMainPlayerCharacter* Player = Cast<AMainPlayerCharacter>(Pawn);
	AMainAIController* AIController = Cast<AMainAIController>(GetController());
	if (Player && AIController)
	{
		AIController->SetFocus(Player, EAIFocusPriority::Move);
		FVector PlayerLocation = Player->GetActorLocation();
		AIController->BlackboardComp->SetValueAsVector(TEXT("TargetLocation"), PlayerLocation);
		AIController->BlackboardComp->SetValueAsObject(TEXT("Player"), Player);

		FVector Moveloc =AIController->BlackboardComp->GetValueAsVector(TEXT("TargetLocation"));
		UE_LOG(LogTemp, Warning, TEXT("SeePlayer Moveloc %s"),*(Moveloc.ToString()));
		bSeenPlayer = true;

	}
}
