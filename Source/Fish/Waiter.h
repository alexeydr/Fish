#pragma once

#include "CoreMinimal.h"
#include "FishCharacter.h"
#include "Fish/Food/FoodDA.h"
#include "Waiter.generated.h"

class AFishChar;

UCLASS()
class FISH_API AWaiter : public AFishCharacter
{
	GENERATED_BODY()

public:

	bool AddOrder(const FDish& Food) 
	{
		if (ClientOrder.Num() < MaxOrder)
		{
			ClientOrder.Add(Food);
			return true;
		} 
		return false;
	};

	const TArray<FDish>& GetCurrentOrder() { return ClientOrder; };
	
	bool AddDish(FDish Food) 
	{
		if (Dishes.Num() < MaxFood)
		{
			Dishes.Add(Food);
			return true;
		} 
		return false;
	};

	void SubmitOrder(TArray<FDish>& ClientOrderArr, AFishChar* Client);
	
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RemoveDish(const FDish& DishForRemove);

	UFUNCTION()
	void MainAction();

	UPROPERTY(Transient)
	TArray<FDish> Dishes;

	UPROPERTY(EditAnywhere)
	int MaxOrder = 5;
	
	UPROPERTY(EditAnywhere)
	int MaxFood = 2;

	UPROPERTY(Transient)
	TArray<FDish> ClientOrder;
	
};
