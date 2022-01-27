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




int	born_philos(t_philos	*all)
{
	int	i;
	int	bool;

	i = 0;
	bool = EXIT_FAILURE;

	while (i < all->numb_of_philos)
	{
		all->body[i].start_time = get_time();

		//pthread_create(&all->body[i].philo_t, NULL, life, &all->body[i]);
		//todo на каждого философа процесс
		all->body[i].pid = fork();
		if (all->body[i].pid == -1)
			exit(error("Child process isn't created\n"));
		if (all->body[i].pid == 0)
		{
			/*printf("[son - %d] pid %d from [parent] pid %d\n",i, getpid(),
				   getppid());*/
			life(&all->body[i]);
			exit(0);
		}
		i++;
	}
//	printf("!!!!! ---- %d\n", i);
//	bool = monitor(all);
/*	i = 0;
	while (i < all->numb_of_philos)
	{
		pthread_detach(all->body[i].philo_t);
		i++;
	}*/
/*
	waitpid(all->body[0].pid, NULL, 0);
	waitpid(all->body[1].pid, NULL, 0);
	waitpid(all->body[2].pid, NULL, 0);
*/
/*	i = 0; //fixme it looks there is no need 'cause exit in every process
	while (i < all->numb_of_philos)
	{

		//kill();
		//wait(NULL);
		waitpid(all->body[i].pid, NULL, 0);
		i++;
	}*/
//	printf("!!!!! ---- %d\n", i);
//	if (all->body[i].required_meals == -1)
//		sem_wait(all->eat_sem);
//	else
	if (all->body[i].required_meals != -1)
		pthread_create(&all->monit_eat, NULL, monit_eat, all);
	sem_wait(all->finish_sem);
	i = 0;
	while (i < all->numb_of_philos)
	{
		kill(all->body[i].pid, SIGTERM); //sigterm better
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
	if (init_philos(argc, argv, all) == EXIT_FAILURE) ///
		return (EXIT_FAILURE);
	exit_code = born_philos(all);
//	end_threads(all);
	return (exit_code);
}
