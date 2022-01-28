/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:17 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death(void *args)
{
	int		i;
	long	time;
	t_param	*philo;

	philo = (t_param *)args;
	while (1)
	{
		time = get_time() - philo->last_eat;
		if (philo->alive == 0 && time >= philo->time_to_die)
		{
			philo->alive = 1;
			message(philo, DIE);
			sem_post(philo->all->finish_sem);
			if (philo->required_meals != -1)
			{
				i = 0;
				while (i < philo->all->numb_of_philos)
				{
					sem_post(philo->all->eat_sem);
					i++;
				}
			}
			return (NULL);
		}
	}
}

void	*monit_eat(void *args)
{
	int			i;
	t_philos	*all;

	i = 0;
	all = (t_philos *)args;
	while (i < all->numb_of_philos)
	{
		sem_wait(all->eat_sem);
		i++;
	}
	sem_post(all->finish_sem);
	return (NULL);
}
