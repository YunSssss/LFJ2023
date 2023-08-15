// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility/MainAttributeSet.h"


AMainPlayerCharacter::AMainPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("FollowCameraBoom"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->TargetArmLength = 500.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	FollowCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComp"));
	FollowCameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	FollowCameraComp->bUsePawnControlRotation = false;

	CharacterMovementComp = GetCharacterMovement();
	if (CharacterMovementComp)
	{
		CharacterMovementComp->bOrientRotationToMovement = true;
		CharacterMovementComp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
		CharacterMovementComp->JumpZVelocity = 700.f;
		CharacterMovementComp->AirControl = 0.35f;
		CharacterMovementComp->MinAnalogWalkSpeed = 20.f;
	}

}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::IA_MoveBindFun);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::IA_LookBindFun);
		EnhancedInputComponent->BindAction(IA_Test, ETriggerEvent::Triggered, this, &AMainPlayerCharacter::IA_TestBindFun);

	}
}

void AMainPlayerCharacter::IA_LookBindFun(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);


	}
}

void AMainPlayerCharacter::IA_MoveBindFun(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainPlayerCharacter::IA_TestBindFun(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("IA_TestBindFun "));
	/*
	UE_LOG(LogTemp, Warning, TEXT("IA_TestBindFun call"));

	if (GetAbilitySystemComponent() == nullptr)
	{
		return;
	}

	GetAbilitySystemComponent()->TryActivateAbilityByClass(TestGA, false);
	
	
	bool CanActive = Value.Get<bool>();
	if (CanActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("IA_TestBindFun call"));

		if (GetAbilitySystemComponent() == nullptr)
		{
			return;
		}

		FGameplayEffectContextHandle  EffectsContext = GetAbilitySystemComponent()->MakeEffectContext();
		EffectsContext.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(TestGe, GetCharacterLevel(), EffectsContext);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(FGameplayEffectSpec(*EffectSpecHandle.Data.Get()), GetAbilitySystemComponent());

		if (MainAttributeSet)
		{
			int Heal = MainAttributeSet->GetHealth();
			UE_LOG(LogTemp, Warning, TEXT("Heal After modify %d"), Heal);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CanActive =FALSE "));
	}
	*/
}

void AMainPlayerCharacter::SetCharacterSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
}

void AMainPlayerCharacter::SetCharacterStop()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.0f;
}

void AMainPlayerCharacter::SetCharacterWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}




