#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main() {
	time_t cur_time;
	struct tm* tm_data;

	time(&cur_time);
	tm_data = localtime(&cur_time);

	printf("Local time %04d-%02d-%02d %02d:%02d:%02d\n",
		tm_data->tm_year + 1900,
		tm_data->tm_mon + 1,
		tm_data->tm_mday,
		tm_data->tm_hour,
		tm_data->tm_min,
		tm_data->tm_sec);
}
