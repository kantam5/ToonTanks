// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

/*
- Base Mesh
- Turren Mesh
- Capsule
- Projectile Spawn Point
- Rotate Turret
- Fire
*/

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDesturction();

protected:
	void RotateTurret(FVector LookAtTarget);

	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coponents", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	// <>���� Ŭ������ ������ ǥ���Ѵ�. ������Ʈ�� �ƴϴ�.
	// C++�� Projectile�� ���� �ڽ��� BP_Projectile�� ������ �� �ִ�. 
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* DeathSound;
};
