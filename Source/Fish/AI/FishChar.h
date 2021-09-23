#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Fish/Food/FoodDA.h"
#include "Fish/Interfaces/InteractionInterface.h"
#include "FishChar.generated.h"

class ABotAIController;
class UWidgetComponent;
class UBotOrderWidget;
class AWaiter;

UCLASS()
class FISH_API AFishChar : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFishChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void WaiterMainAction();

	void WaiterTakeOrder(AWaiter* InWaiter);

	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(Transient)
	ABotAIController* AiController;

	UPROPERTY(Transient)
	TArray<FDish> Order;
		
	UPROPERTY(Transient)
	TArray<FDish> UnacceptedOrder;

	UPROPERTY(Transient)
	UBotOrderWidget* WidgetRef;

public:	
	
	bool CanTakeFood(const FDish& InFood);

	void UpdateOrderWidget();
	
	UPROPERTY(Transient)
	float Tips;

	void AddFoodInOrder(const FDish& Dish);

	virtual void MainAction(ECharacterTypes Type);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
