// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// HitComp : ���� �ε�ģ ��ü�� ������Ʈ ����
// OtherActor : �߻�Ǽ� �ε��� ��ü ����ü
// OtherComp : �߻�Ǽ� �ε��� ��ü�� ������Ʈ ����
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FString HitCompName = HitComp->GetName();
	FString OtherActorName = OtherActor->GetName();
	FString OtherCompName = OtherComp->GetName();
	UE_LOG(LogTemp, Warning, TEXT("HitCompName: %s"), *HitCompName);
	UE_LOG(LogTemp, Warning, TEXT("OtherActorName: %s"), *OtherActorName);
	UE_LOG(LogTemp, Warning, TEXT("OtherCompName: %s"), *OtherCompName);
}