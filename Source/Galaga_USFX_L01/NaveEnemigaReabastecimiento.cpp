// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaReabastecimiento.h"

ANaveEnemigaReabastecimiento::ANaveEnemigaReabastecimiento()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));

	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);
}

void ANaveEnemigaReabastecimiento::Mover(float DeltaTime)
{
	/*FVector PosicionActual = GetActorLocation();


	float NuevaX = FMath::RandRange(-1000.0f, 1000.0f) * (DeltaTime / 1000.0f);
	float NuevaY = FMath::RandRange(-1000.0f, 1000.0f) * (DeltaTime / 1000.0f);
	float NuevaZ = FMath::RandRange(-1000.0f, 1000.0f) * DeltaTime;

	FVector NuevaPosicion = FVector(PosicionActual.X + NuevaX, PosicionActual.Y + NuevaY, PosicionActual.Z + NuevaZ);

	SetActorLocation(NuevaPosicion);*/
	static FVector PosicionActual = GetActorLocation();

	static float TopeAbajo = PosicionActual.X - 1300.0f;
	static float Reaparicion = PosicionActual.X + 200.0f;
	static float MovimientoY = 0.0f;


	FVector Desplazamiento = FVector(-125.0f * DeltaTime, MovimientoY * DeltaTime, FMath::RandRange(-500.0f, 500.0f) * DeltaTime);

	FVector ReaparicionPocision = GetActorLocation() + Desplazamiento;
	if (ReaparicionPocision.X < TopeAbajo)
	{
		ReaparicionPocision.X = Reaparicion;
	}
	SetActorLocation(ReaparicionPocision);
}

void ANaveEnemigaReabastecimiento::Disparar()
{

}

void ANaveEnemigaReabastecimiento::Destruirse()
{

}

void ANaveEnemigaReabastecimiento::Escapar()
{
}
void ANaveEnemigaReabastecimiento::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}