// Shoot Them Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUPGAME_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "0.00", ClampMax = "1000.00"))
	float MaxHealth = 100.f;

    float GetHealth() const { return Health; }

	UFUNCTION(BLueprintCallable)
    bool IsDead() const { return Health <= 0.00f; }

	FOnDeath OnDeath;

	FOnHealthChange OnHealthChange;

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

    float Health = 0.f;

	UFUNCTION()
	void OnTakeDamageHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
