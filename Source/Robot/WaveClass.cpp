// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveClass.h"

WaveClass::WaveClass()
{
	maxSpawnSize = 5;
}

WaveClass::WaveClass(int spawnSize)
{
	maxSpawnSize = spawnSize;
}

WaveClass::~WaveClass()
{
}

void WaveClass::UpdateMaxSpawnSize(int newSpawnSize)
{
	maxSpawnSize = newSpawnSize;
}

int WaveClass::GetAmountToSpawn(EnemyType enemy)
{
	return gameWave[(BYTE)enemy][currentWave];
}

void WaveClass::Spawned(EnemyType enemy, BYTE numberSpawned)
{
	gameWave[(BYTE)enemy][currentWave] -= numberSpawned;	
}

bool WaveClass::HasEnemiesToSpawn()
{
	return (gameWave[(BYTE)EnemyType::Walking][currentWave] + gameWave[(BYTE)EnemyType::Flying][currentWave]) > 0;
}

bool WaveClass::HasNextWave()
{
	return (currentWave < 20);
}

void WaveClass::NextWave()
{
	currentWave++;
}

int WaveClass::GetSpawnSize()
{
	return maxSpawnSize;
}


