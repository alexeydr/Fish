#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FishTypes.generated.h"

class AFishGameMode;
class AFoodSpawnTable;
class AWaiter;

UENUM(BlueprintType)
enum class EIngredient : uint8
{	
	Bread,
	Sausage,
	Cheese
};

UENUM()
enum class EActions : uint8
{	
	Main,
	Additionally
};

UENUM()
enum class ECharacterTypes : uint8
{	
	None,
	Waiter
};

USTRUCT()
struct FIngredient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText IngredientName;

	UPROPERTY(EditAnywhere)
	EIngredient Ingredient;
};


UCLASS()
class UHelper : public UObject
{
	GENERATED_BODY()

public:

	static AFishGameMode* GetGameMode();
	
	static AFoodSpawnTable* GetSpawnTable();

	static AWaiter* GetWaiterCharacter(UWorld* World);

};