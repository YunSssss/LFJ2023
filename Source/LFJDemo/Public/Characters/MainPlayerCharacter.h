// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MainCharacterBase.h"
#include "MainPlayerCharacter.generated.h"

/**
 * 
 */

class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;

UCLASS()
class LFJDEMO_API AMainPlayerCharacter : public AMainCharacterBase
{
	GENERATED_BODY()


public:
	AMainPlayerCharacter();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:
	UFUNCTION()
	void IA_LookBindFun(const FInputActionValue& Value);

	UFUNCTION()
	void IA_MoveBindFun(const FInputActionValue& Value);

	UFUNCTION()
	void IA_TestBindFun(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void SetCharacterSprint();

	UFUNCTION(BlueprintCallable)
	void SetCharacterWalk();

	UFUNCTION(BlueprintCallable)
	void SetCharacterStop();

public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UCameraComponent* FollowCameraComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterMovementComponent* CharacterMovementComp = nullptr;

	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction*  IA_Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* IA_Look;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInputAction* IA_Test;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class  UGameplayEffect> TestGe;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class  UGameplayAbility> TestGA;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//class UInputAction* IA_Jump;



};
