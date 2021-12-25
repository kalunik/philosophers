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

void ft_msleep(long ms)
{
	long	begin;

	begin = get_time();
	usleep(ms * 920);
	while (get_time() < begin + ms)
		usleep(ms * 3);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void message(t_param *philo, const char *text)
{
	size_t	text_size;

	text_size = ft_strlen(text);
	pthread_mutex_lock(philo->write_text);
	printf("%-8ld ms", get_time() - philo->start_time);
	if (text_size == DIE_TEXT_SIZE)
		printf("\033[1;31m");
	printf(" %d %s",philo->id, text);
	if (text_size == DIE_TEXT_SIZE)
		printf("\033[0m");
	if (ft_strlen(text) != DIE_TEXT_SIZE)
		pthread_mutex_unlock(philo->write_text);
}

void eating(t_param	*philo)
{
	pthread_mutex_lock(philo->l_fork);
	message(philo, TAKE_FORK_L);

	pthread_mutex_lock(philo->r_fork);
	message(philo, TAKE_FORK_R);

	message(philo, EAT);
	ft_msleep(philo->time_to_eat);
	philo->last_eat = get_time();

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void sleeping(t_param	*philo)
{
	message(philo, SLEEP);
	ft_msleep(philo->time_to_sleep);
}

void thinking(t_param	*philo)
{
	message(philo, THINK);
}

void *life(void *args)
{
	t_param	*philo;

	philo = (t_param *)args;
	if (philo->id % 2 == 0)
		usleep(100);

	while (philo->alive == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void *monitor(t_philos *all)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < all->numb_of_philos)
		{
			//printf("!! %ld - %d\n", get_time() - all->body[i].last_eat,
			//	   all->body[i].time_to_die);
			if (all->body[i].alive == 0 && get_time() - all->body[i]
			.last_eat >= all->body[i].time_to_die)
			{
				all->body[i].alive = 1;
				message(&all->body[i], DIE);
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
}

void born_philos(t_philos	*all)
{
	int			i;

	i = 0;

	while (i < all->numb_of_philos)
	{
		all->body[i].start_time = get_time();
		//printf("%d process\n", all->body[i].id);
		pthread_create(&all->body[i].philo_t, NULL, life, &all->body[i]);
		i++;
	}
	monitor(all);
	i = 0;
/*	while (i < all->numb_of_philos)
	{
		pthread_join(all->body[i].philo_t, NULL);
		i++;
	}*/
}

int	main(int argc, char **argv)
{
	int			i;
	t_philos	*all;

//	if(parse_args(argc, argv, &philo) == EXIT_FAILURE)
//		return (EXIT_FAILURE);
	all = malloc(sizeof(t_philos));
	if (!all)
		return (EXIT_FAILURE);
	init_philos(argc, argv, all);

//	i = 0;
//	while (i < all->numb_of_philos) ///посмотреть форки
//	{
//		printf("%d %d\n", all->body[i].l_fork, all->body[i]
//		.r_fork);
//		i++;
//	}

	born_philos(all);
	return (0);
}


