#include <time.h>
#include <windows.h>
#include <intrin.h>
#include <stdio.h>
#pragma intrinsic(__rdtsc)

unsigned __int64 PassTime;
unsigned __int64 tick(){return (__rdtsc());}

void StartTimer()
{
	PassTime = tick();
}

unsigned __int64 StopTimer()
{
	unsigned __int64 ElapsedTime = 0;
	ElapsedTime = tick() - PassTime;
return ElapsedTime;
}