// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MainCharacterBase.h"
#include "MainAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class LFJDEMO_API AMainAICharacter : public AMainCharacterBase
{
	GENERATED_BODY()
	
public:
	AMainAICharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardComponent* BlackboardComp;

	UFUNCTION()
	void OnSeenPawn(APawn* Pawn);

	bool bSeenPlayer =false;

};
