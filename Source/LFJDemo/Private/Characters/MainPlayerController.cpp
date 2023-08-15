// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainPlayerController.h"
#include "Characters/MainCharacterBase.h"
#include "AbilitySystemComponent.h"

AMainPlayerController::AMainPlayerController()
{
}

void AMainPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	UE_LOG(LogTemp, Warning, TEXT("AcknowledgePossession call"));

	AMainCharacterBase* PlayerChara = Cast<AMainCharacterBase>(P);
	if (PlayerChara != nullptr)
	{
		PlayerChara->AbilitySystemComp->InitAbilityActorInfo(PlayerChara, PlayerChara);
	}
}
