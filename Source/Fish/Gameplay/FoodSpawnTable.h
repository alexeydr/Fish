#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fish/Food/FoodDA.h"
#include "Fish/Interfaces/InteractionInterface.h"
#include "FoodSpawnTable.generated.h"

UCLASS()
class FISH_API AFoodSpawnTable : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodSpawnTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SpawnFood(const FDish& DishForSpawn);

	void OnWaiterInteraction();

	UPROPERTY(Transient)
	TArray<FDish> Queue;

	UPROPERTY(Transient)
	uint8 bIsSpawnStarted : 1;

public:	
	
	void StartParseQueue();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void MainAction(ECharacterTypes Type);



};
