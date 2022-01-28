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

#include "philo_bonus.h"

void	message(t_param *philo, const char *text)
{
	sem_wait(philo->all->write_sem);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, text);
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

int	life(t_param *philo)
{
	pthread_create(&philo->death, NULL, death, philo);
	while (philo->alive == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (EXIT_FAILURE);
}
