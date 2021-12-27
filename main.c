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
	if (text_size == TAKE_FORK_TEXT_SIZE)
		printf("\033[0;36m");
	else if (text_size == EAT_TEXT_SIZE)
		printf("\033[1;34m");
	else if (text_size == DIE_TEXT_SIZE)
		printf("\033[1;31m");
	printf(" %d %s\n",philo->id, text);
	if (text_size != UNUSED_TEXT_SIZE)
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

	if (philo->required_meals != -1)
		philo->meal_counter++;
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

int monitor(t_philos *all)
{
	int	i;
	int count = 0;
	i = 0;
	while (1)
	{
		while (i < all->numb_of_philos)
		{
			if (all->body[i].alive == 0 && get_time() - all->body[i].last_eat
			>= all->body[i].time_to_die)
			{
				all->body[i].alive = 1;
				message(&all->body[i], DIE);
				return (EXIT_SUCCESS);
			}
			if (all->body[i].meal_counter >= all->body->required_meals &&
			all->body->required_meals != -1)
			{
				count++;
				int j = 0;
				pthread_mutex_lock(&all->write_text);
				while (j < all->numb_of_philos)
				{
					printf(" %d - ", all->body[j].meal_counter);
					j++;
				}
				printf("\n");
				pthread_mutex_unlock(&all->write_text);
				if (count == all->numb_of_philos)
					return (EXIT_SUCCESS);
			}
			i++;
		}
		i = 0;
		count = 0;
	}
}

int born_philos(t_philos	*all)
{
	int	i;
	int	bool;

	i = 0;
	bool = EXIT_FAILURE;
	while (i < all->numb_of_philos)
	{
		all->body[i].start_time = get_time();
		pthread_create(&all->body[i].philo_t, NULL, life, &all->body[i]);
		i++;
	}
	bool = monitor(all);
	i = 0;
	while (i < all->numb_of_philos)
	{
		pthread_detach(all->body[i].philo_t);
		i++;
	}
	if (i != all->numb_of_philos)
		bool = EXIT_FAILURE;
	return (bool);
}

int	main(int argc, char **argv)
{
	int			i;
	t_philos	*all;
	int			exit_code;

//	if(parse_args(argc, argv, &philo) == EXIT_FAILURE)
//		return (EXIT_FAILURE);
	all = malloc(sizeof(t_philos));
	if (!all)
		return (EXIT_FAILURE);
	init_philos(argc, argv, all); //todo проверка входящих значений на
	// валидность

//	i = 0;
//	while (i < all->numb_of_philos) ///посмотреть форки
//	{
//		printf("%d %d\n", all->body[i].l_fork, all->body[i]
//		.r_fork);
//		i++;
//	}

	exit_code = born_philos(all); //todo free, destroy mutex
	//printf("exit code!! %d\n", exit_code);
	return (exit_code);
}


