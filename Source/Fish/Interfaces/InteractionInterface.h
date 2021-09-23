// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fish/FishTypes.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FISH_API IInteractionInterface
{
	GENERATED_BODY()

public:

	virtual void MainAction(ECharacterTypes Type) {};

	virtual void AdditionallyAction(ECharacterTypes Type) {};
};
