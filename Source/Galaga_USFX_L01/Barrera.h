// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrera.generated.h"

UCLASS()
class GALAGA_USFX_L01_API ABarrera : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mallaBarrera;
	
private:
	float resistencia; //Numero de disparos que puede recibir antes de ser destruido
	float peso;
	float volumen;
	FVector posicion;
public:	
	// Sets default values for this actor's properties
	ABarrera();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
