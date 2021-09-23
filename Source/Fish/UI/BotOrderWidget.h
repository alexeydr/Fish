#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Fish/Food/FoodDA.h"
#include "BotOrderWidget.generated.h"

class UHorizontalBox;

UCLASS()
class FISH_API UBotOrderWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ClearFoodContainer();

	void AddDishImage(const FDish& Dish);

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* DishesContainer;
	
};
