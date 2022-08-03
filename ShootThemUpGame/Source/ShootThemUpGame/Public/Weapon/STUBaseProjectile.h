// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUPGAME_API ASTUBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent = nullptr;

public:	
	

};
