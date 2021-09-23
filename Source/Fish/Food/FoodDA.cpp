#include "FoodDA.h"

const FDish& UFoodDA::GetRandomDish()
{
	return Food[FMath::RandRange(0, Food.Num() - 1)];
}
