// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneComponentBarrera.h"

// Sets default values for this component's properties
USceneComponentBarrera::USceneComponentBarrera()
{


	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Crear el componente de malla estática
	//SceneComponentBarrera = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SceneComponentBarrera"));

	//// Cargar la malla desde un archivo
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BarreraMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	

	//SceneComponentBarrera->SetStaticMesh(BarreraMesh.Object);
	


}

void USceneComponentBarrera::CrearBarrera()
{
	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		FTransform ComponentTransform (this->GetComponentTransform());
		TheWorld->SpawnActor(BarreraToSpawn, &ComponentTransform);
	}

}


// Called when the game starts
void USceneComponentBarrera::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USceneComponentBarrera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

