// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveClass.h"

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

int WaveClass::GetAmountLeftToSpawn(EnemyType enemy)
{
	return gameWave[(BYTE)enemy][currentWave];
}

void WaveClass::Spawned(EnemyType enemy, BYTE numberSpawned)
{
	gameWave[(BYTE)enemy][currentWave] -= numberSpawned;
}
