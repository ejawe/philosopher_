#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void	*myturn(void *arg)
{
	int *iptr = (int *)malloc(sizeof(int));
	*iptr = 5;
	for(int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("My Turn! %d %d\n", i, *iptr);
		(*iptr)++;
	}
	return iptr;
}

void yourturn()
{
	for(int i = 0; i < 3; i++)
	{
		sleep(1);
		printf("Your Turn %d\n", i);
	}
}

int main(void)
{
	pthread_t newthread;

	int *result;

	pthread_create(&newthread, NULL, myturn, NULL);

	//yourturn();

	pthread_join(newthread, (void *)&result);
	printf("thread's done: *result=%d\n", *result);

	return 0;

}
