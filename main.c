/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:17 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_life(void	*arg)
{
	t_philos	*all;

	all = arg;
	pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < all->body->time_to_eat; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("[%d]	%d -- eating\n", i, all->body->numb_of_philos);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int	create_philos(t_philos	*all)
{
	int				i;
	pthread_t		th[2];

	for (i = 0; i < 2; i++)
	{
		if (pthread_create(&th[i], NULL, philo_life, &all)) //создается философ
			// и делает рутину(ест, спит, думает
		{
			printf("Failed to create a thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philos	all;

	parse_args(argc, argv, &all);
	create_philos(&all);
	return (0);
}


