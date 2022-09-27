// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

UBaseGameplayAbility::UBaseGameplayAbility()
{
	
}

//void UBaseGameplayAbility::ActivateEffectUI(UGameplayEffect* Effect)
//{

//}

bool UBaseGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         FGameplayTagContainer* OptionalRelevantTags)
{
	if (CommitCheck(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		//ActivateEffectUI(GetCostGameplayEffect());
	}
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//ActivateEffectUI(GetCooldownGameplayEffect());
}
