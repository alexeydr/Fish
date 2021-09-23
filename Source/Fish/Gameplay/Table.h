#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Table.generated.h"

class UChildActorComponent;
class AFishChar;

UCLASS()
class FISH_API ATable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetEmptyChair();

	static ATable* GetRandomTable();

	void AddClient(AFishChar* NewClient) { 
		if (NewClient)
			Clients.Add(NewClient);
	};

	void RemoveClient(AFishChar* OldClient) {
		if (OldClient)
			Clients.Remove(OldClient);
	};

private:

	UPROPERTY(Transient)
	TArray<AFishChar*> Clients;

	int MaxSeats = 0;


};
