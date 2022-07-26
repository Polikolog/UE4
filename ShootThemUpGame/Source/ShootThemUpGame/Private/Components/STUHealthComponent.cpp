// Shoot Them Up Game, All Rights Reserved


#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
    OnHealthChange.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeDamageHandler);
	}
}

void USTUHealthComponent::OnTakeDamageHandler(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
        return;

    Health = FMath::Clamp<float>(Health - Damage, 0.00f, MaxHealth);
    OnHealthChange.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }


	if (DamageType)
    {
        if (DamageType->IsA<USTUFireDamageType>())
        {
            
		}
        if (DamageType->IsA<USTUIceDamageType>())
        {
            
        }
	}
}
