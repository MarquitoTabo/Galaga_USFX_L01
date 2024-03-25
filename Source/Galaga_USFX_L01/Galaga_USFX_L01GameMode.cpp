// Copyright Epic Games, Inc. All Rights Reserved.

#include "Galaga_USFX_L01GameMode.h"
#include "Galaga_USFX_L01Pawn.h"
#include "NaveEnemiga.h"
#include "NaveEnemigaTransporte.h"
#include "MyNaveEnemigaCaza.h"
#include "NaveEnemigaEspia.h"
#include "NaveEnemigaNodriza.h"
#include "NaveEnemigaReabastecimiento.h"
#include "MyNaveEnemigaCazaG1.h"
#include "MyNaveEnemigaCazaG2.h"
#include "NaveEnemigaTransporteG1.h"
#include "NaveEnemigaTransporteG2.h"
#include "NaveEnemigaEspiaG1.h"
#include "NaveEnemigaEspiaG2.h"
#include "NaveEnemigaNodrizaG1.h"
#include "NaveEnemigaNodrizaG2.h"
#include "NaveEnemigaReabastecimientoG1.h"
#include "NaveEnemigaReabastecimientoG2.h"
#include "Components/SceneComponent.h"
#include "SceneComponentBarrera.h"

AGalaga_USFX_L01GameMode::AGalaga_USFX_L01GameMode()
{
	// set default pawn class to our character class
	PrimaryActorTick.bCanEverTick = true;
	DefaultPawnClass = AGalaga_USFX_L01Pawn::StaticClass();

	//NaveEnemiga01 = nullptr;
}

void AGalaga_USFX_L01GameMode::BeginPlay()
{
	Super::BeginPlay();
	//set the game satate to playing
	FVector ubicacionInicioNavesEnemigasCaza = FVector(-500.0f, 500.0f, 200.0f);
	FVector ubicacionInicioNavesEnemigasTransporte = FVector(500.0f, 500.0f, 200.0f);
	FVector ubicacionInicioNAvesEnemigasReabastecimiento = FVector(1000.0f, 500.0f, 200.0f);

	/*FVector ubicacionNave01 = FVector(0.0f, 1000.0f, 200.0f);
	FVector ubicacionNave02 = FVector(0.0f, 700.0f, 200.05f);
	FVector ubicacionNave03 = FVector(0.0f, 400.0f, 200.0f);
	FVector ubicacionNave04 = FVector(0.0f, 100.0f, 200.05f);
	FVector ubicacionNave05 = FVector(0.0f, -200.0f, 200.0f);
	FVector ubicacionNave06 = FVector(-250.0f, 700.0f, 200.05f);
	FVector ubicacionNave07 = FVector(-500.0f, 700.0f, 200.0f);
	FVector ubicacionNave08 = FVector(-250.0f, 1000.0f, 200.05f);
	FVector ubicacionNave09 = FVector(-500.0f, 1000.0f, 200.0f);
	FVector ubicacionNave10 = FVector(-250.0f, 400.0f, 200.05f);
	FVector ubicacionNave11 = FVector(-500.0f, 400.0f, 200.0f);
	FVector ubicacionNave12 = FVector(-250.0f, 100.0f, 200.05f);
	FVector ubicacionNave13 = FVector(-500.0f, 100.0f, 200.0f);
	FVector ubicacionNave14 = FVector(-250.0f, -200.0f, 200.05f);
	FVector ubicacionNave15 = FVector(-500.0f, -200.0f, 200.0f);*/

	FRotator rotacionNave = FRotator(0.0f, 0.0f, 0.0f);

	UWorld* const World = GetWorld();


	if (World != nullptr)
	{
	TArray<TSubclassOf<ANaveEnemiga>> claseNave = { AMyNaveEnemigaCazaG1::StaticClass(), AMyNaveEnemigaCazaG2::StaticClass(),ANaveEnemigaEspiaG1::StaticClass(),ANaveEnemigaEspiaG2::StaticClass(),
	ANaveEnemigaNodrizaG1::StaticClass(),ANaveEnemigaNodrizaG2::StaticClass(),ANaveEnemigaReabastecimientoG1::StaticClass(),ANaveEnemigaReabastecimientoG2::StaticClass(),
	ANaveEnemigaTransporteG1::StaticClass(),ANaveEnemigaTransporteG2::StaticClass() };

	FVector InicialSpawnLocation = FVector(100.f, -500.f, 200.f);

		for (int i = 0; i < 30; i++)
		{
			TSubclassOf<ANaveEnemiga> ClaseRandom = claseNave[FMath::RandRange(0, claseNave.Num() - 1)];

			FVector SpawnLocation = InicialSpawnLocation + FVector(0.f,i* 80.f, 0.f);

			FRotator SpawnRotation = FRotator::ZeroRotator;
			ANaveEnemiga* NuevaNaveSpawn = GetWorld()->SpawnActor<ANaveEnemiga>(ClaseRandom, SpawnLocation, SpawnRotation);

			if (NuevaNaveSpawn)
			{

			}

			/*FVector PosicionNaveActual = FVector(ubicacionInicioNavesEnemigasCaza.X, ubicacionInicioNavesEnemigasCaza.Y + i * 300, ubicacionInicioNavesEnemigasCaza.Z);
			AMyNaveEnemigaCaza* NaveEnemigaCazaTemporal = World->SpawnActor<AMyNaveEnemigaCaza>(PosicionNaveActual, rotacionNave);
			TANavesEnemigas.Push(NaveEnemigaCazaTemporal);*/

			
			//FVector PosicionNaveTransActual = FVector(ubicacionInicioNavesEnemigasTransporte.X, ubicacionInicioNavesEnemigasTransporte.Y + i * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			//ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = World->SpawnActor<ANaveEnemigaTransporte>(PosicionNaveActual, rotacionNave);
			//TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
		}

		/*float nevaPosicionX = ubicacionInicioNavesEnemigasTransporte.X - 300.0f;

		for (int j = 0; j < 4; j++)
		{
			FVector PosicionNaveActual = FVector(ubicacionInicioNavesEnemigasTransporte.X, ubicacionInicioNavesEnemigasTransporte.Y + j * 300, ubicacionInicioNavesEnemigasTransporte.Z);
			ANaveEnemigaTransporte* NaveEnemigaTransporteTemporal = World->SpawnActor<ANaveEnemigaTransporte>(PosicionNaveActual, rotacionNave);

			TANavesEnemigas.Push(NaveEnemigaTransporteTemporal);
		}*/
		// spawn the projectile
		/*NaveEnemigaTransporte01 = World->SpawnActor<ANaveEnemigaTransporte>(ubicacionNave01, rotacionNave); 
	    MyNaveEnemigaCaza01 = World->SpawnActor<AMyNaveEnemigaCaza>(ubicacionNave02, rotacionNave);
		NaveEnemigaEspia01 = World->SpawnActor<ANaveEnemigaEspia>(ubicacionNave03, rotacionNave);
		NaveEnemigaNodriza01 = World->SpawnActor<ANaveEnemigaNodriza>(ubicacionNave04, rotacionNave);
		NaveEnemigaReabastecimiento01 = World->SpawnActor<ANaveEnemigaReabastecimiento>(ubicacionNave05, rotacionNave);
		MyNaveEnemigaCazaG101 = World->SpawnActor<AMyNaveEnemigaCazaG1>(ubicacionNave06, rotacionNave);
		MyNaveEnemigaCazaG201 = World->SpawnActor<AMyNaveEnemigaCazaG2>(ubicacionNave07, rotacionNave);
		NaveEnemigaTransporteG101 = World->SpawnActor<ANaveEnemigaTransporteG1>(ubicacionNave08, rotacionNave);
		NaveEnemigaTransporteG201 = World->SpawnActor<ANaveEnemigaTransporteG2>(ubicacionNave09, rotacionNave);
		NaveEnemigaEspiaG101 = World->SpawnActor<ANaveEnemigaEspiaG1>(ubicacionNave10, rotacionNave);
		NaveEnemigaEspiaG201 = World->SpawnActor<ANaveEnemigaEspiaG2>(ubicacionNave11, rotacionNave);
		NaveEnemigaNodrizaG101 = World->SpawnActor<ANaveEnemigaNodrizaG1>(ubicacionNave12, rotacionNave);
		NaveEnemigaNodrizaG201 = World->SpawnActor<ANaveEnemigaNodrizaG2>(ubicacionNave13, rotacionNave);
		NaveEnemigaReabastecimientoG101 = World->SpawnActor<ANaveEnemigaReabastecimientoG1>(ubicacionNave14, rotacionNave);
		NaveEnemigaReabastecimientoG201 = World->SpawnActor<ANaveEnemigaReabastecimientoG2>(ubicacionNave15, rotacionNave);*/
	}

	/*MyNaveEnemigaCaza01->SetPosicion(FVector(-500.0f, 500.0f, 200.0f));
	NaveEnemigaTransporte01->SetPosicion(FVector(500.0f, 500.0f, 200.0f));
	NaveEnemigaEspia01->SetPosicion(FVector(0.0f, 500.0f, 200.0f));
	NaveEnemigaNodriza01->SetPosicion(FVector(1000.0f, 0.0f, 130.0f));
	NaveEnemigaReabastecimiento01->SetPosicion(FVector(3000.0f, 100.0f, 500.0f));
	MyNaveEnemigaCazaG101->SetPosicion(FVector(200.0f, 0.0f, 200.0f));
	MyNaveEnemigaCazaG201->SetPosicion(FVector(600.0f, 250.0f, 200.0f));
	NaveEnemigaTransporteG101->SetPosicion(FVector(200.0f, 0.0f, 200.0f));
	NaveEnemigaTransporteG201->SetPosicion(FVector(600.0f, 250.0f, 200.0f));
	NaveEnemigaEspiaG101->SetPosicion(FVector(200.0f, 0.0f, 200.0f));
	NaveEnemigaEspiaG201->SetPosicion(FVector(600.0f, 250.0f, 200.0f));
	NaveEnemigaNodrizaG101->SetPosicion(FVector(200.0f, 0.0f, 200.0f));
	NaveEnemigaNodrizaG201->SetPosicion(FVector(600.0f, 250.0f, 200.0f));
	NaveEnemigaReabastecimientoG101->SetPosicion(FVector(200.0f, 0.0f, 200.0f));
	NaveEnemigaReabastecimientoG201->SetPosicion(FVector(600.0f, 250.0f, 200.0f));*/

	TMapPowerUp.Add(3000, "escudo");
	TMapPowerUp.Add(200, "doble tiro");
	TMapPowerUp.Add(1000, "vida extra");
	TMapPowerUp.Add(1500, "invulnerable");
	TMapPowerUp.Add(500, "velocidad");

	PowerUpStatusMap.Add(3000, false);
	PowerUpStatusMap.Add(200, false);
	PowerUpStatusMap.Add(1000, false);
	PowerUpStatusMap.Add(1500, false);
	PowerUpStatusMap.Add(500, false);
	score = 0;
}


void AGalaga_USFX_L01GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiempoTranscurrido++;
	if (TiempoTranscurrido >= 100)
	{
		int numeroEnemigo = FMath::RandRange(0, 9);
		if (GEngine)
		{

		}
		score = score + 50;
		TiempoTranscurrido = 0;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("score: %d"), score));
	}
	for (const auto& par : TMapPowerUp)
	{
		int scoreMap = par.Key;
		FString PowerUp = par.Value;
		if (scoreMap == score)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("PowerUp: %s"), *PowerUp));
		}
		for (auto& par2 : PowerUpStatusMap)
		{
			int PowerUpScore = par2.Key;
			bool& bPowerUpStatus = par2.Value;

			if (score >= PowerUpScore && !bPowerUpStatus)
			{
				bPowerUpStatus = true;
				FString StatusMessage = FString::Printf(TEXT("PowerUp with score %d is now active: %s"), PowerUpScore, bPowerUpStatus ? TEXT("True") : TEXT("False"));
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, StatusMessage);
			}
		}

	}
	
}
