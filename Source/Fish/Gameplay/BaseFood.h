#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fish/Interfaces/InteractionInterface.h"
#include "Fish/FishTypes.h"
#include "Fish/Food/FoodDA.h"
#include "BaseFood.generated.h"

UCLASS()
class FISH_API ABaseFood : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void WaiterAction();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void MainAction(ECharacterTypes Type) override;

	UPROPERTY(Transient)
	FDish CurrentDish;

};
