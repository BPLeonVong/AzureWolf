#include "AzureWolfStd.h"

#include "AWTime.h"

namespace AW
{
	#include <sys/timeb.h>
	static long gsInitialSec = 0;
	static long gsInitialUSec = 0;
	static bool gsInitializedTime = false;
	
	int64_t GetTimeInMicroseconds ()
	{
	   struct timeb currentTime;

		if (!gsInitializedTime)
		{
			gsInitializedTime = true;
			ftime(&currentTime);
			gsInitialSec = (long)currentTime.time;
			gsInitialUSec = 1000*currentTime.millitm;
		}

		ftime(&currentTime);
		long currentSec = (long)currentTime.time;
		long currentUSec = 1000*currentTime.millitm;
		long deltaSec = currentSec - gsInitialSec;
		long deltaUSec = currentUSec - gsInitialUSec;
		if (deltaUSec < 0)
		{
			deltaUSec += 1000000;
			--deltaSec;
		}
		return 1000000*deltaSec + deltaUSec;
	}

	double GetTimeInSeconds ()
	{
		int64_t microseconds = GetTimeInMicroseconds();
		return 1e-06*microseconds;
	}

}