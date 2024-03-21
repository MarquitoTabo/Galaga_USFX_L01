// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNaveEnemigaCaza.h"

AMyNaveEnemigaCaza::AMyNaveEnemigaCaza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_TriPyramid.Shape_TriPyramid'"));
	//// Create the mesh component
	//mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	mallaNaveEnemiga->SetStaticMesh(ShipMesh.Object);

}


void AMyNaveEnemigaCaza::Mover(float DeltaTime)
{
	static FVector PosicionActual = GetActorLocation();

	static float TopeAbajo = PosicionActual.X - 1300.0f;
	static float Reaparicion = PosicionActual.X + 200.0f;
	static float MovimientoY = 0.0f;


	FVector Desplazamiento = FVector(-50.0f * DeltaTime, MovimientoY * DeltaTime, FMath::RandRange(-500.0f, 500.0f) * DeltaTime);

	FVector ReaparicionPocision = GetActorLocation() + Desplazamiento;
	if (ReaparicionPocision.X < TopeAbajo)
	{
		ReaparicionPocision.X = Reaparicion;
	}
	SetActorLocation(ReaparicionPocision);

}



void AMyNaveEnemigaCaza::Disparar()
{

}

void AMyNaveEnemigaCaza::Destruirse()
{

}

void AMyNaveEnemigaCaza::Escapar()
{

}

void AMyNaveEnemigaCaza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Mover(DeltaTime);
}