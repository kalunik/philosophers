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

long get_time(void)
{
	struct timeval	tp;
	long			ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

//void	*philo_life(void	*arg)
//{
//	t_philos	*philo;
//
//	philo = arg;
//
//	//pthread_mutex_init(&philo->body->write_text, NULL);
//	for (int i = 0; i < philo->body->time_to_eat; i++)
//	{
//		//pthread_mutex_lock(&philo->body->write_text);
//		printf("fdsmjfg");
//		//printf("[%d]	%d -- eating\n", i, philo->body->numb_of_philos);
//		//pthread_mutex_unlock(&philo->body->write_text);
//	}
//	return NULL;
//}

void *life(void *args)
{
	t_param	*philo;

	philo = args;

	printf("%d started dinner: %d : %d \n", philo->id, philo->l_fork,
		   philo->r_fork);

	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork); // проверить откуда идёт i до num philos

	printf("%d is eating\n", philo->id);

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);

	printf("%d finished dinner\n", philo->id);
	return (NULL);
}

void born_philos(t_philos	*all)
{
	pthread_t	philo[200];
	int			i;

	i = 0;
	while (i++ < all->numb_of_philos)
	{
		//printf("%d is eating\n", all->body->id);
		pthread_create(&philo[i], NULL, life, &all->body[i]);
	}
	i = 1;
	while (i++ <= all->numb_of_philos)
	{
		pthread_join(philo[i], NULL);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_philos	all;

//	if(parse_args(argc, argv, &philo) == EXIT_FAILURE)
//		return (EXIT_FAILURE);
	init_philos(argc, argv, &all);

	i = 0;
	while (i <all.numb_of_philos)
	{
		all.body->id = i;
		printf("%d %d\n", all.body[all.body->id].l_fork, all.body[all.body->id]
		.r_fork);
		i++;
	}

	born_philos(&all);
	return (0);
}


