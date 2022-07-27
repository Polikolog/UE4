// Shoot Them Up Game, All Rights Reserved


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Weapon/STUBaseWeapon.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("Health Component");

    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("Text Render Component");
    TextRenderComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    check(HealthComponent) 
    check(CameraComponent)
    check(GetCharacterMovement())

    OnHealthChange(HealthComponent->GetHealth());

    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChange.AddUObject(this, &ASTUBaseCharacter::OnHealthChange);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);

    SpawnWeapon();
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::BeginSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::EndSprint);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASTUBaseCharacter::BeginCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASTUBaseCharacter::EndCrouch);
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) { return 0.f; }
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngelBetween = FMath::Acos(FVector::DotProduct(VelocityNormal, GetActorForwardVector()));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    float Degrees = FMath::RadiansToDegrees(AngelBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    if (Amount == 0.f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::LookUp(float Amount)
{
    if (Amount == 0.f)
        return;
	AddControllerPitchInput(Amount);
}

void ASTUBaseCharacter::TurnAround(float Amount)
{
    if (Amount == 0.f)
        return;
	AddControllerYawInput(Amount);
}

void ASTUBaseCharacter::BeginSprint() 
{
    GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void ASTUBaseCharacter::EndSprint() 
{
    GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ASTUBaseCharacter::BeginCrouch() 
{
    Crouch();
}

void ASTUBaseCharacter::EndCrouch() 
{
    UnCrouch();
}

void ASTUBaseCharacter::OnDeath() 
{
    PlayAnimMontage(DeathAnimMotage);

    //HealthComponent->DestroyComponent();

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChange(float Health) 
{
    TextRenderComponent->SetText(FString::SanitizeFloat(Health, 0));
    auto Time = GetWorld()->GetTimeSeconds();
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) 
{
    const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;

    if (FallVelocityZ < LandedDamageVelocity.X)
        return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTUBaseCharacter::SpawnWeapon() 
{
    if (!ensure(GetWorld())) return;
    const auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(BaseWeapon);
    if (!ensure(Weapon))
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(GetMesh(), AttachmentRules, "WeaponPoint");
}
