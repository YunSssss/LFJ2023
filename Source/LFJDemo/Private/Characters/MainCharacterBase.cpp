// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility/MainAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacterBase::AMainCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	
	MainAttributeSet = CreateDefaultSubobject<UMainAttributeSet>(TEXT("MainAttributeSet"));
}

// Called when the game starts or when spawned
void AMainCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Warning, TEXT("PossessedBy call"));
	if (AbilitySystemComp !=nullptr)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}

	ApplyCharacterEffects();

	ApplyCharacterAbilities();

	if (MainAttributeSet )
	{
		int Health = MainAttributeSet->GetHealth();
		int MaxHealth = MainAttributeSet->GetMaxHealth();
		int Mana = MainAttributeSet->GetMana();
		int MaxMana = MainAttributeSet->GetMaxMana();
		int  MoveSpeed= MainAttributeSet->GetMoveSpeed();
		int MaxMoveSpeed = MainAttributeSet->GetMaxMoveSpeed();
		UE_LOG(LogTemp, Warning, TEXT("Health : %d "),Health);
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth : %d"),MaxHealth);
		UE_LOG(LogTemp, Warning, TEXT("Mana : %d"),Mana);
		UE_LOG(LogTemp, Warning, TEXT("MaxMana : %d"),MaxMana);
		UE_LOG(LogTemp, Warning, TEXT("MoveSpeed : %d"),MoveSpeed);
		UE_LOG(LogTemp, Warning, TEXT("MaxMoveSpeed : %d") , MaxMoveSpeed);
		GetCharacterMovement()->MaxWalkSpeed = MainAttributeSet->GetMoveSpeed();
	}
}

UAbilitySystemComponent* AMainCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

int AMainCharacterBase::GetCharacterLevel()
{
	return CharacterLevel;
}

void AMainCharacterBase::SetCharacterLevel(int NewLevel)
{
	CharacterLevel = NewLevel;
}

void AMainCharacterBase::SetCharacterHasApplyAbilities(bool bSetAbilities)
{
	bCharacterHasApplyAbilities = bSetAbilities;
}

bool AMainCharacterBase::GetCharacterHasApplyAbilities()
{
	return bCharacterHasApplyAbilities;
}

void AMainCharacterBase::ApplyCharacterEffects()
{
	if (GetAbilitySystemComponent() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetAbilitySystemComponent() == nullptr"));
		return;
	}
	if (EffectsWhenStartUp.Num() <=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("EffectsWhenStartUp.IsEmpty() == false"));
		return;
	}

	FGameplayEffectContextHandle  EffectsContext = GetAbilitySystemComponent()->MakeEffectContext();
	EffectsContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& GameplayEffect : EffectsWhenStartUp )
	{
		FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectsContext);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(FGameplayEffectSpec(*EffectSpecHandle.Data.Get()), GetAbilitySystemComponent());
	}

}

void AMainCharacterBase::ClearCharacterEffects()
{
	if (GetAbilitySystemComponent() == nullptr || EffectsWhenStartUp.IsEmpty() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetAbilitySystemComponent() == nullptr || EffectsWhenStartUp.IsEmpty() == false"));
		return;
	}
	FGameplayEffectQuery GameplayEffectQuery;
	GameplayEffectQuery.EffectSource = this;
	GetAbilitySystemComponent()->RemoveActiveEffects(GameplayEffectQuery);
}

void AMainCharacterBase::ApplyCharacterAbilities()
{

	if (GetCharacterHasApplyAbilities() == true || GetAbilitySystemComponent() == nullptr || AbilitiesWhenStartUp.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCharacterHasApplyAbilities() == true || GetAbilitySystemComponent() == nullptr || AbilitiesWhenStartUp.IsEmpty() == true"));
		return;
	}

	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesWhenStartUp)
	{
		
		FGameplayAbilitySpec GameplayAbilitySpec(Ability,GetCharacterLevel(),NULL, this);
		GetAbilitySystemComponent()->GiveAbility(GameplayAbilitySpec);
	}

	SetCharacterHasApplyAbilities(true);
	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	GetAbilitySystemComponent()->GetAllAbilities(OutAbilityHandles);
	UE_LOG(LogTemp, Warning, TEXT("aB count %d"), OutAbilityHandles.Num());
}

void AMainCharacterBase::ClearCharacterAbilities()
{
	if (GetCharacterHasApplyAbilities() == false || GetAbilitySystemComponent() == nullptr || AbilitiesWhenStartUp.IsEmpty() == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetCharacterHasApplyAbilities() == false || GetAbilitySystemComponent() == nullptr || AbilitiesWhenStartUp.IsEmpty() == true"));
		return;
	}

	GetAbilitySystemComponent()->ClearAllAbilities();
	SetCharacterHasApplyAbilities(false);
}
