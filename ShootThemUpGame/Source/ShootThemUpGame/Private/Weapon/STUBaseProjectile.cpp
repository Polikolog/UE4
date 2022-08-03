// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseProjectile.h"
#include "Components/SphereComponent.h"

ASTUBaseProjectile::ASTUBaseProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

}

void ASTUBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}
