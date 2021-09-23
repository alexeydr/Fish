#include "Fish/UI/BotOrderWidget.h"	
#include "Components/Image.h"
#include "Components/HorizontalBox.h"

void UBotOrderWidget::ClearFoodContainer()
{
	DishesContainer->ClearChildren();
}

void UBotOrderWidget::AddDishImage(const FDish& Dish)
{
	UImage* DishImage = NewObject<UImage>(this);
	if (DishImage && DishesContainer)
	{
		DishImage->SetBrushFromTexture(Dish.Texture);
		DishesContainer->AddChild(DishImage);
	}
}