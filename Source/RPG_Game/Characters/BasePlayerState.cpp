// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

#include "RPG_Game/BaseAttributeSet.h"
#include "RPG_Game/Components/BaseAbilitySystemComponent.h"

ABasePlayerState::ABasePlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UBaseAttributeSet>("Attributes");

	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBaseAttributeSet* ABasePlayerState::GetAttributeSetBase() const
{
	return Attributes;
}
