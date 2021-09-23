#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Fish/Food/FoodDA.h"
#include "DishSaver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FISH_API UDishSaver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDishSaver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
