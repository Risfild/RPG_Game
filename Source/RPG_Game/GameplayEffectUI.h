// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Windows.ApplicationModel.Activation.h>

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "UObject/Interface.h"
#include "GameplayEffectUI.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UGameplayEffectUI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_GAME_API IGameplayEffectUI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void ActivateUI(UGameplayEffect* Effect) const;
};
