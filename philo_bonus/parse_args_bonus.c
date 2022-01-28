/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:08:33 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 19:12:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parse_args(t_philos	*all, int argc, char **argv, int i)
{
	memset((void *)&all->body[i], 0, sizeof(t_param));
	all->body[i].id = i + 1;
	all->body[i].time_to_die = ft_atoi(argv[2]);
	all->body[i].time_to_eat = ft_atoi(argv[3]);
	all->body[i].time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->body[i].required_meals = ft_atoi(argv[5]);
	else
		all->body[i].required_meals = -1;
	all->body[i].last_eat = get_time();
	all->body[i].pid = -2;
	all->body[i].all = all;
}

static inline int	validate_params(int argc, t_philos	*all)
{
	if (all->numb_of_philos < 1 || all->body->time_to_die < 0
		|| all->body->time_to_eat < 0 || all->body->time_to_sleep < 0
		|| (argc == 6 && all->body->required_meals < 0))
		return (error("Invalid args\n"));
	return (EXIT_SUCCESS);
}

static inline void	*philo_sem_open_1(t_philos	*all)
{
	sem_unlink("/forks");
	all->fork_sem = sem_open("/forks", O_CREAT, 0, all->numb_of_philos);
	if (all->fork_sem == SEM_FAILED)
		exit (error("Failed to open semaphore for forks\n"));
	sem_unlink("/forks");
	sem_unlink("/write");
	all->write_sem = sem_open("/write", O_CREAT | O_EXCL, 0, 1);
	if (all->write_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		exit (error("Failed to open semaphore for write\n"));
	}
	sem_unlink("/write");
	return (EXIT_SUCCESS);
}

static inline void	*philo_sem_open_2(t_philos	*all)
{
	sem_unlink("/finish_sem");
	all->finish_sem = sem_open("/finish_sem", O_CREAT | O_EXCL, 0, 0);
	if (all->finish_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		sem_close(all->write_sem);
		exit (error("Failed to open semaphore for finish\n"));
	}
	sem_unlink("/finish_sem");
	sem_unlink("/eat_sem");
	all->eat_sem = sem_open("/eat_sem", O_CREAT | O_EXCL, 0, 0);
	if (all->eat_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		sem_close(all->write_sem);
		sem_close(all->finish_sem);
		exit (error("Failed to open semaphore for eat\n"));
	}
	sem_unlink("/eat_sem");
	return (EXIT_SUCCESS);
}

int	init_philos(int argc, char **argv, t_philos	*all)
{
	int	i;

	if (!(argc == 5 || argc == 6))
		return (error("There should be 4 or 5 arguments\n"));
	all->numb_of_philos = ft_atoi((argv[1]));
	all->body = (t_param *) malloc(sizeof(t_param) * all->numb_of_philos);
	if (all->body == NULL)
		exit (error("Can't malloc for body"));
	philo_sem_open_1(all);
	philo_sem_open_2(all);
	i = 0;
	while (i < all->numb_of_philos)
		parse_args(all, argc, argv, i++);
	if (validate_params(argc, all))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
