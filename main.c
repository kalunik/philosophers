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


void	*philo_life(void	*arg)
{
	t_philos	*all;

	all = arg;

	//pthread_mutex_init(&all->body->write_text, NULL);
	for (int i = 0; i < all->body->time_to_eat; i++)
	{
		//pthread_mutex_lock(&all->body->write_text);
		printf("fdsmjfg");
		//printf("[%d]	%d -- eating\n", i, all->body->numb_of_philos);
		//pthread_mutex_unlock(&all->body->write_text);
	}
	return NULL;
}

void	init_philos(t_philos	*all, int argc, char **argv,int i)
{
	all->body[i].id = i + 1;
	all->body[i].time_to_die = ft_atoi(argv[2]);
	all->body[i].time_to_eat = ft_atoi(argv[3]);
	all->body[i].time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->body[i].required_meals = ft_atoi(argv[5]);
	else
		all->body[i].required_meals = -1;
	all->body[i].l_fork = &all->fork[i];
	all->body[i].r_fork = &all->fork[(i + 1) % all->numb_of_philos];
	all->body[i].write_text = &all->write_text;
	all->body[i].start_pr = 0;
	all->body[i].last_eat = 0;
}
int	create_philos(int argc, char **argv,t_philos	*all)
{
	int i;

	i = 0;
	all->numb_of_philos = ft_atoi((argv[1]));
	all->body = (t_param *)malloc(sizeof(t_param) * all->numb_of_philos);
	if (all->body == NULL)
		return (EXIT_FAILURE);
	all->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
			all->numb_of_philos);
	//
	//all->write_text = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	while (i < all->numb_of_philos)
	{
		pthread_mutex_init(all->fork, NULL);
		i++;
	}
	pthread_mutex_init(&all->write_text, NULL);
	i = 0;
	while (i < all->numb_of_philos)
	{
		init_philos(all, argc, argv, i);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos	all;

//	if(parse_args(argc, argv, &all) == EXIT_FAILURE)
//		return (EXIT_FAILURE);
	create_philos( argc, argv, &all);
	int i =0;
	while (i < all.numb_of_philos)
	{
		printf("%d %d\n", all.body[i].l_fork, all.body[i].r_fork);
		i++;
	}
	return (0);
}


