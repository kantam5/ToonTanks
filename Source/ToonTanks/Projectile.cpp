// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->MaxSpeed = 1300.0f;
	ProjectileMovementComponent->InitialSpeed = 1300.0f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSound,
			GetActorLocation()
		);
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// HitComp : 가서 부딪친 물체의 컴포넌트 종류
// OtherActor : 발사되서 부딪힌 물체 그자체
// OtherComp : 발사되서 부딪힌 물체의 컴포넌트 종류
// 여기서 ApplyDamage를 호출하여 OtherActor의 OnTakeAnyDamage가 호출되어 OtherActor의 HealthComponent의 DamageTaken이 호출된다. 
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation()
			);
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation()
			);
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitCameraShakeClass);
		}
		
		Destroy();
	}

	Destroy(); 
}