// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ROBOT_API WaveClass
{
public:
	WaveClass();
	WaveClass(int spawnSize);
	~WaveClass();

	enum EnemyType
	{
		Walking,
		Flying
	};

	void UpdateMaxSpawnSize(int newSpawnSize);

	int GetAmountToSpawn(EnemyType enemy);

	void Spawned(EnemyType enemy, BYTE numberSpawned);

	bool HasEnemiesToSpawn();

	bool HasNextWave();

	void NextWave();

	int GetSpawnSize();

private:

	int currentWave = 0;

	//20 = amount of enemies in the wave
	//2 = the types of enemies
	//(enemiesPerWave*Wave)/enemy probablility = amount of enemies in the wave
	BYTE gameWave[2][20] = { {10,20,25,40, 0,30,30,30,35, 0,30,35,40,45,50,55,60,65,70,80},		//Waling
							 {5 , 5, 5, 5,40,10,15,20,15,50,20,25,20,20,20,20,20,20,20,25} };	//Flying
	
	//The amount of enemies that will be spawned at one time
	int maxSpawnSize = 5;
};
