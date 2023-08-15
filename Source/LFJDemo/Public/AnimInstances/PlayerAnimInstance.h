// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LFJDEMO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMainPlayerCharacter* PlayerCharacter;

	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
