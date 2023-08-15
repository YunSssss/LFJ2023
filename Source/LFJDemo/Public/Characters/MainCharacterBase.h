// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MainCharacterBase.generated.h"


class UAbilitySystemComponent;
class UMainAttributeSet;

UCLASS()
class LFJDEMO_API AMainCharacterBase : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;


public:
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComp  = nullptr;

	UPROPERTY()
	UMainAttributeSet* MainAttributeSet = nullptr;

	FORCEINLINE	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	int GetCharacterLevel();

	UFUNCTION()
	void SetCharacterLevel(int NewLevel);

	UFUNCTION()
	void SetCharacterHasApplyAbilities(bool bSetAbilities);

	UFUNCTION()
	bool GetCharacterHasApplyAbilities();

	UFUNCTION()
	void ApplyCharacterEffects();

	UFUNCTION()
	void ClearCharacterEffects();

	UFUNCTION()
	void ApplyCharacterAbilities();

	UFUNCTION()
	void ClearCharacterAbilities();


public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<TSubclassOf<class  UGameplayEffect>> EffectsWhenStartUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class  UGameplayAbility>> AbilitiesWhenStartUp;

private:
	int CharacterLevel = 1;

	bool bCharacterHasApplyAbilities = false;

};
