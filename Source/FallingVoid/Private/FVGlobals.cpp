// Copyright: Falling Void Studios


#include "FVGlobals.h"

void FVGlobals::LogToScreen(const FString& message, FColor color)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, color, message);
}
