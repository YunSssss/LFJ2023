// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/MainAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Characters/MainPlayerCharacter.h"

UMainAttributeSet::UMainAttributeSet()
{
}

void UMainAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute,NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		ClampAttribute(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if(Attribute == GetMaxManaAttribute())
	{
		ClampAttribute(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	else if (Attribute == GetMaxMoveSpeedAttribute())
	{
		ClampAttribute(MoveSpeed, MaxMoveSpeed, NewValue, GetMoveSpeedAttribute());
	}
}

void UMainAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	AController* TargetController = nullptr;
	AMainPlayerCharacter* TargetAvatarCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetAvatarCharacter = Cast<AMainPlayerCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		SetMoveSpeed(FMath::Clamp(GetMoveSpeed(), 0.0f, GetMaxMoveSpeed()));
		
	}
}

void UMainAttributeSet::ClampAttribute(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComp = GetOwningAbilitySystemComponent();
	float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComp)
	{
		float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilitySystemComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}

}
