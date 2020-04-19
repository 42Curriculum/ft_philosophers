#include<sys/time.h>
#include<pthread.h>
#include<stdio.h>
#include <unistd.h>


int main()
{
	struct timeval t;
	struct timeval t2;
	time_t count;

	gettimeofday(&t, NULL);
	while (1)
	{
		gettimeofday(&t2, NULL);
		count = t2.tv_usec - t.tv_usec;
		printf("Elapsed time usec : %ld\n", count);
		count = t2.tv_sec - t.tv_sec;
		printf("Elapsed time :sec : %ld\n", count);
		sleep(1);
	}
}