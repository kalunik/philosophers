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

#include "philo_bonus.h"

static inline int	philo_kill(t_philos	*all)
{
	int	i;

	i = 0;
	while (i < all->numb_of_philos)
	{
		if (kill(all->body[i].pid, SIGTERM) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static inline int	finish_and_close(t_philos	*all)
{
	if (philo_kill(all))
		return (error("Couldn't kill process\n"));
	if (sem_close(all->fork_sem) == -1)
		return (error("Couldn't close fork_sem"));
	if (sem_close(all->write_sem) == -1)
		return (error("Couldn't close write_sem"));
	if (sem_close(all->finish_sem) == -1)
		return (error("Couldn't close finish_sem"));
	if (all->body[0].required_meals != -1)
	{
		if (pthread_detach(all->monit_eat) != 0)
			return (error("Couldn't detach thread"));
	}
	free (all->body);
	free (all);
	return (EXIT_SUCCESS);
}

static inline void	philo_fork(t_philos	*all)
{
	int	i;

	i = 0;
	while (i < all->numb_of_philos)
	{
		all->body[i].start_time = get_time();
		all->body[i].pid = fork();
		if (all->body[i].pid == -1)
			exit(error("Child process isn't created\n"));
		if (all->body[i].pid == 0)
			exit(life(&all->body[i]));
		i++;
	}
}

int	born_philos(t_philos	*all)
{
	philo_fork(all);
	if (all->body[0].required_meals != -1 && all->numb_of_philos > 1)
	{
		if (pthread_create(&all->monit_eat, NULL, monit_eat, all) != 0)
			exit(error("Can't create thread for eat count"));
	}
	sem_wait(all->finish_sem);
	if (finish_and_close(all))
		exit(EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philos	*all;

	all = malloc(sizeof(t_philos));
	if (!all)
		return (EXIT_FAILURE);
	if (init_philos(argc, argv, all) == EXIT_FAILURE)
		exit (EXIT_FAILURE);
	born_philos(all);
	return (EXIT_SUCCESS);
}
