/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:17 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	message(t_param *philo, const char *text)
{
	size_t	text_size;

	text_size = ft_strlen(text);

	//todo семафор на текст
	//pthread_mutex_lock(philo->write_text);
	//	printf("%p\n", &philo->all->write_sem);
	sem_wait(philo->all->write_sem);

	printf("%ld", get_time() - philo->start_time);
/*	if (text_size == TAKE_FORK_TEXT_SIZE)
		printf("\033[0;36m");
	else if (text_size == EAT_TEXT_SIZE)
		printf("\033[1;34m");
	else if (text_size == DIE_TEXT_SIZE)
		printf("\033[1;31m");*/
	printf(" %d %s\n", philo->id, text);
/*	if (text_size != UNUSED_TEXT_SIZE)
		printf("\033[0m");

	if (ft_strlen(text) != DIE_TEXT_SIZE)
		pthread_mutex_unlock(philo->write_text);*/
	sem_post(philo->all->write_sem);
}

void	eating(t_param	*philo)
{
	sem_wait(philo->all->fork_sem);
	message(philo, TAKE_FORK);
	sem_wait(philo->all->fork_sem);
	message(philo, TAKE_FORK);

	message(philo, EAT);
	ft_msleep(philo->time_to_eat);
	philo->last_eat = get_time();
	if (philo->required_meals != -1)
	{
		philo->meal_counter++;
		if (philo->meal_counter == philo->required_meals)
			sem_post(philo->all->eat_sem);
	}
//	pthread_mutex_unlock(philo->l_fork);
//	pthread_mutex_unlock(philo->r_fork);
	sem_post(philo->all->fork_sem);
	sem_post(philo->all->fork_sem);
}

void	sleeping(t_param	*philo)
{
	message(philo, SLEEP);
	ft_msleep(philo->time_to_sleep);
}

void	thinking(t_param	*philo)
{
	message(philo, THINK);
}

void	*death(void *args)
{
	t_param	*philo;

	philo = (t_param *)args;
	while (1)
	{
		int time;
		time = get_time() - philo->last_eat;
		if (philo->alive == 0 && get_time() - philo->last_eat >= philo->time_to_die)
		{
			printf("%d - time to eat || id %d\n", time, philo->id);
			philo->alive = 1;
			message(philo, DIE);
			sem_post(philo->all->finish_sem);
			return (NULL);
		}
	}
}

void	*monit_eat(void *args)
{
	int	i;
	int	count;
	t_param	*philo;

	i = 0;
	count = 0;
	philo = (t_param *)args;

	while (1)
	{
		while (i < philo->all->numb_of_philos)
		{
			printf("i - %d ||[%d] -- time %d\n",i, philo->id,
				   philo->all->body->time_to_die);
			sem_wait(philo->all->eat_sem);
			i++;
		}
		printf("i - %d ||[%d] -- time %d\n",i, philo->id,
			   philo->all->body->time_to_die);
//		if (count == philo->all->numb_of_philos)
		exit (EXIT_SUCCESS);
//			if (is_alive(i, philo->all) == EXIT_SUCCESS)
//				return (EXIT_SUCCESS);
//			if (philo->meal_counter >= philo->required_meals
//				&& philo->required_meals != -1)
//			{
//				count++;
//				if (count == all->numb_of_philos)
//					return (EXIT_SUCCESS);
//			}
//			i++;
//		}
//		i = 0;
//		count = 0;
	}
	return (NULL);
}

int	life(t_param *philo)
{
	pthread_create(&philo->death, NULL, death, philo);
	/*if (philo.required_meals != -1)
		pthread_create(&philo.monit_eat, NULL, monit_eat,&philo);*/
//	if (philo.id % 2 == 0)
//		usleep(100); //todo посмотреть не опасно ли юзать, мона отправлятьспать
	while (philo->alive == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (EXIT_FAILURE);
}
