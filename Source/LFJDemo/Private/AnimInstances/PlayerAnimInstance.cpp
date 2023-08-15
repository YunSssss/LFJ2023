// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/MainPlayerCharacter.h"
#include "KismetAnimationLibrary.h"


void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	PlayerCharacter = Cast<AMainPlayerCharacter>(TryGetPawnOwner());

	if (PlayerCharacter != nullptr)
	{
		FVector CharaVelocity = PlayerCharacter->GetVelocity();
		MoveSpeed = CharaVelocity.Size();
		MoveDirection = UKismetAnimationLibrary::CalculateDirection(CharaVelocity, PlayerCharacter->GetActorRotation());
		InAir = PlayerCharacter->GetCharacterMovement()->IsFalling();
		
	}
}
