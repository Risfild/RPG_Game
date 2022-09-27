// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "BasePlayerState.h"
#include "RPG_Game/BaseAttributeSet.h"
#include "RPG_Game/BaseGameplayAbility.h"
#include "RPG_Game/Components/BaseAbilitySystemComponent.h"


UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ABaseCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UBaseGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent -> GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), 
				this));
		}
	}
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Server GAS init
	ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		InitializeAttributes();
		GiveAbilities();
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Client GAS init
	ABasePlayerState* PS = GetPlayerState<ABasePlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBaseAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		InitializeAttributes();

		if (AbilitySystemComponent && InputComponent)
		{
			const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EAbilityInputID", static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
			AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
		}
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EAbilityInputID", static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}
