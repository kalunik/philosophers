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

#include "philo_b.h"

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
	/// вилка уже не назначается
//	all->body[i].l_fork = &all->fork[i];
//	all->body[i].r_fork = &all->fork[(i + 1) % all->numb_of_philos];

	/// todo сем на письмо
//	all->body[i].write_text = &all->write_text;
}

static inline int	validate_params(int argc, t_philos	*all)
{
	if (all->numb_of_philos < 1 || all->body->time_to_die < 0
		|| all->body->time_to_eat < 0 || all->body->time_to_sleep < 0
		|| (argc == 6 && all->body->required_meals < 0))
		return (error("Invalid args\n"));
	return (EXIT_SUCCESS);
}


int	init_philos(int argc, char **argv, t_philos	*all)
{
	int i;

	if (!(argc == 5 || argc == 6))
		return (error("There should be 4 or 5 arguments\n"));
	all->numb_of_philos = ft_atoi((argv[1]));
	all->body = (t_param *) malloc(sizeof(t_param) * all->numb_of_philos);
	if (all->body == NULL)
		return (EXIT_FAILURE);
	sem_unlink("/forks");
	all->fork_sem = sem_open("/forks", O_CREAT, 0777, all->numb_of_philos);
	if (all->fork_sem == SEM_FAILED)
		return (error("Failed to open semaphore for forks\n"));
	i = 0;
	sem_unlink("/write");
	all->write_sem = sem_open("/write", O_CREAT, 0777, 1);
	if (all->write_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		return (error("Failed to open semaphore for write\n"));
	}
	sem_unlink("/finish_sem");
	all->finish_sem = sem_open("/finish_sem", O_CREAT, 0777, 0);
	if (all->finish_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		sem_close(all->write_sem);
		return (error("Failed to open semaphore for finish\n"));
	}
	sem_unlink("/eat_sem");
	all->eat_sem = sem_open("/eat_sem", O_CREAT, 0777, 0);
	if (all->eat_sem == SEM_FAILED)
	{
		sem_close(all->fork_sem);
		sem_close(all->write_sem);
		sem_close(all->finish_sem);
		return (error("Failed to open semaphore for eat\n"));
	}
	while (i < all->numb_of_philos)
	{
		parse_args(all, argc, argv, i++);
	}
	if (validate_params(argc, all))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
