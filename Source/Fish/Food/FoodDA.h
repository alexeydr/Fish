#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Fish/FishTypes.h"
#include "FoodDA.generated.h"

/**
 * 
 */
class ABaseFood;

USTRUCT()
struct FDish
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText DishName;

	UPROPERTY(EditAnywhere)
	TArray<EIngredient> Ingredients;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseFood> ActForSpawn;

	UPROPERTY(EditAnywhere)
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere)
	float CookingTime;

	UPROPERTY(EditAnywhere)
	float Cost;

	bool operator== (const FDish& left)
	{
		return (left.DishName.ToString() == DishName.ToString());
	}	
	
	friend bool operator== (const FDish& left,const FDish& right)
	{
		return (left.DishName.ToString() == right.DishName.ToString());
	}
};

UCLASS()
class UFoodDA : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere)
	TArray<FDish> Food;

	const FDish& GetRandomDish();

};
