// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SceneComponentBarrera.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALAGA_USFX_L01_API USceneComponentBarrera : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USceneComponentBarrera();


	UFUNCTION(BlueprintCallable, Category = "Barrera")
		void CrearBarrera();

		UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BarreraToSpawn;

		//UStaticMeshComponent* SceneComponentBarrera;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
