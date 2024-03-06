// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NaveEnemiga.generated.h"

class UstaticMeshComponent;

UCLASS()
class GALAGA_USFX_L01_API ANaveEnemiga : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* NaveEnemigaMesh;  //malla nave enemigo

private:
	
	float resistencia;
	float velocidad;
	float danoProducido;
	FString nombre;
	float tiempoDisparo;
	FVector posicion;

public:
	FORCEINLINE float GetResistencia() const { return resistencia; }
	FORCEINLINE float GetVelocidad() const { return velocidad; }
	FORCEINLINE float GetDanoProducido() const { return danoProducido; }
	FORCEINLINE FString GetNombre() const { return nombre; }
	FORCEINLINE float GetTiempoDisparo() const { return tiempoDisparo; }
	FORCEINLINE FVector Getposicion() const { return posicion; }

	FORCEINLINE void SetResistencia(float _resistencia) { resistencia = _resistencia; }
	FORCEINLINE void SetVelocidad(float _velocidad) { velocidad = _velocidad; }
	FORCEINLINE void SetDanoProducido(float _velocidad) { velocidad = _velocidad; }
	FORCEINLINE void SetNombre(FString _nombre) { nombre = _nombre; }
	FORCEINLINE void SetTiempoDisparo(float _tiempoDisparo) { tiempoDisparo = _tiempoDisparo; }
	FORCEINLINE void SetPosicion(FVector _posicion) { posicion = _posicion; }


public:
	// Sets default values for this actor's properties
	ANaveEnemiga();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
