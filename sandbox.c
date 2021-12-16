#include <pthread.h>
#include <stdio.h>

int				mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	//parse_args(argc, argv);
	pthread_t	th[4];
	int			i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL)) //создается философ
			// и делает рутину(ест, спит, думает)
		{
			printf("Failed to create a thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		//if (pthread_join(th[i], NULL))
		//	return (2);
		printf("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Numbers of mails : %d\n", mails);
	return (1);
}
