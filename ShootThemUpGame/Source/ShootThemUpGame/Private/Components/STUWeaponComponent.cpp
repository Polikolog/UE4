// Shoot Them Up Game, All Rights Reserved


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
    SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
    if (!ensure(GetWorld())) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!ensure(Character)) return;

    CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(BaseWeapon);
    if (!ensure(CurrentWeapon)) return;
    
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);

    CurrentWeapon->SetOwner(Character);
}

void USTUWeaponComponent::Fire() 
{
    if (!ensure(CurrentWeapon)) return;
    CurrentWeapon->Fire();
}
