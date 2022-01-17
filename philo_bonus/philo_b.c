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

#include "philo_b.h"

static inline int	is_alive(int i, t_philos *all)
{
	if (all->body[i].alive == 0 && get_time() - all->body[i].last_eat
		>= all->body[i].time_to_die)
	{
		all->body[i].alive = 1;
		message(&all->body[i], DIE);
		return (EXIT_SUCCESS);
	}
	return (2);
}

int	monitor(t_philos *all)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (1)
	{
		while (i < all->numb_of_philos)
		{
			if (is_alive(i, all) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
			if (all->body[i].meal_counter >= all->body->required_meals
				&& all->body->required_meals != -1)
			{
				count++;
				if (count == all->numb_of_philos)
					return (EXIT_SUCCESS);
			}
			i++;
		}
		i = 0;
		count = 0;
	}
}

int	born_philos(t_philos	*all)
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
	t_philos	*all;
	int			exit_code;

	exit_code = 0;
	all = malloc(sizeof(t_philos));
	if (!all)
		return (EXIT_FAILURE);
	if (init_philos(argc, argv, all) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exit_code = born_philos(all);
	end_threads(all);
	return (exit_code);
}
