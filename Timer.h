// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PROJECTGAME_API Timer
{
public:
	Timer();
	UFUNCTION(BlueprintCallable, Category = PlayerAbility)
	void Countdown();
};
