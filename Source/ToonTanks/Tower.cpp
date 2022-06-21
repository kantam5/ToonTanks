// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find the Distance to the Tank
	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

// ȣ���� ToonTanksGameMode����
void ATower::HandleDestruction()
{
	Super::HandleDesturction();

	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// Fire every 2seconds
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle, 
		this, 
		&ATower::CheckFireCondition, 
		FireRate, 
		true
	);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}

	if (InFireRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// Check to see if the Tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	
	return false;
}
