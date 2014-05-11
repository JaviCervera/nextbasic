#include "time.h"
#include "platform.h"
#include "string.h"
#include <string.h>
#include <time.h>

using namespace std;

EXPORT int CALL Millisecs() {
    return plat_Millisecs();
}

EXPORT void CALL Delay(int msecs) {
    plat_Delay(msecs);
}

EXPORT string CALL CurrentDate() {
	time_t timer;
    time(&timer);
	struct tm* timeinfo = localtime(&timer);
	return LSet(Str(timeinfo->tm_mday), 2, "0") + " " + LSet(Str(timeinfo->tm_mon+1), 2, "0") + " " + LSet(Str(timeinfo->tm_year+1900), 4, "0");
}

EXPORT string CALL CurrentTime() {
    time_t timer;
    time(&timer);
	struct tm* timeinfo = localtime(&timer);
	return LSet(Str(timeinfo->tm_hour), 2, "0") + ":" + LSet(Str(timeinfo->tm_min), 2, "0") + ":" + LSet(Str(timeinfo->tm_sec), 2, "0");
}
