// Copyright: Falling Void Studios


#include "FVGlobals.h"

#include "Kismet/GameplayStatics.h"

void FVGlobals::LogToScreen(const FString& message, FColor color)
{
	/*if (GEngine && m_ShouldLog)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, color, message);*/
}

void FVGlobals::SetShouldLog(bool value)
{
	m_ShouldLog = value;
}
