#include "FPSProject\Manager/ItemSpawnManager.h"

// Ammo
#include "FPSProject\Object/Ammo/CPP_LightAmmoStock.h"

// Gun
#include "FPSProject\Object/Gun/AR/CPP_Gun_R301.h"

// Sets default values
AItemSpawnManager::AItemSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Item"));
	}
}

// Called when the game starts or when spawned
void AItemSpawnManager::BeginPlay()
{
	Super::BeginPlay();

		FActorSpawnParameters params;
		{
			// LightAmmo¶¬
			for (auto point : m_SpawnPoints_LightAmmo)
			{
				if (point)
				{
					auto something =
						GetWorld()->SpawnActor<ACPP_LightAmmoStock>
						(point->GetActorLocation()
							, point->GetActorRotation()
							, params
							);
				}
			}

			// R-301¶¬
			for (auto r301point : m_SpawnPoints_R301)
			{
				if (r301point)
				{
					auto something =
						GetWorld()->SpawnActor<ACPP_Gun_R301>
						(r301point->GetActorLocation()
							, r301point->GetActorRotation()
							, params
							);
				}
			}
		}
}

// Called every frame
void AItemSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

