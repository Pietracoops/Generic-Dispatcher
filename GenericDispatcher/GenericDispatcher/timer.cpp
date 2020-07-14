#include "GenericDispatcher.h"


using namespace std;

double get_time()
{
	//returns time in seconds 1 second = 1000000000 nanoseconds
	auto timeNow = boost::chrono::high_resolution_clock::now().time_since_epoch();		// initial clock time
	auto timeSinceEpoch = boost::chrono::duration_cast<boost::chrono::nanoseconds>(timeNow).count();
	double output = (double)timeSinceEpoch;

	output = output / 1000000000;
	return output;
}

double high_resolution_time()
// windows high resolution time function
{
	static int init = 0;
	static double pow32, count_low0, count_high0;
	double t, count_low, count_high, timer_frequency;
	LARGE_INTEGER count;

	if (init == 0) {
		pow32 = pow(2.0, 32); // calculate a constant, 2^32
		QueryPerformanceCounter(&count); // get initial count
		count_low0 = count.LowPart;
		count_high0 = count.HighPart;
		init = 1;
	}

	// read the timer frequency
	QueryPerformanceFrequency(&count);
	timer_frequency = count.LowPart;

	// read the timer
	QueryPerformanceCounter(&count);
	count_low = count.LowPart - count_low0;
	count_high = count.HighPart - count_high0;

	// calculate the time
	t = (count_low + count_high*pow32) / timer_frequency;

	return t;
}
