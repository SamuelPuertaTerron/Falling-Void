// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"

class AFVPlayerBase;
/**
 *  A class for Globals Function that come in useful
 */
class FALLINGVOID_API FVGlobals
{
public:

	static void LogToScreen(const FString& message, FColor color = FColor::Green);

	static void SetShouldLog(bool value);

private:
	inline static bool m_ShouldLog = true;
};

#define LOG(Message, ...) 	UE_LOG(LogTemp, Warning, TEXT(Message), ##__VA_ARGS__);

