// Copyright: Falling Void Studios

#pragma once

#include "CoreMinimal.h"

/**
 *  A class for Globals Function that come in useful
 */
class FALLINGVOID_API FVGlobals
{
public:
	FVGlobals();
	~FVGlobals();

	static void LogToScreen(const FString& message, FColor color = FColor::Green);

	static void SetShouldLog(bool value);

private:
	inline static bool m_ShouldLog = true;
};
