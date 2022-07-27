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

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeDamageHandler);
	}
}

void USTUHealthComponent::OnTakeDamageHandler(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    
    if (Damage <= 0.0f || IsDead() || !GetOwner())
        return;

    GetOwner()->GetWorldTimerManager().ClearTimer(OutTimer);

    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHealing)
    {
        GetOwner()->GetWorldTimerManager().SetTimer(OutTimer, this, &USTUHealthComponent::Heal, UpdateTimeHealing, true, DelayHealing);
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

void USTUHealthComponent::Heal()
{
    SetHealth(Health + RangeHealing);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetOwner())
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(OutTimer);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.00f, MaxHealth);
    OnHealthChange.Broadcast(Health);
}
