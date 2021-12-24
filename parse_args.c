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

#include "philo.h"

/*int parse_args(int argc, char **argv, t_philos *all)
{
	all->body = malloc(sizeof(t_param));
	if (!all->body)
		return (EXIT_FAILURE);
	if (!(argc == 5 || argc == 6))
	{
		printf("Give me 4 or 5 arguments\n");
		return (EXIT_FAILURE);
	}
	memset((void *)all->body, 0, sizeof(t_param));
//	all->numb_of_philos = ft_atoi(argv[1]);
//	all->body->time_to_die = ft_atoi(argv[2]);
//	all->body->time_to_eat = ft_atoi(argv[3]);
//	all->body->time_to_eat = ft_atoi(argv[4]);
//	if (argc == 6)
//		all->body->required_meals = ft_atoi(argv[5]);
	if (all->numb_of_philos < 1 || all->body->time_to_die < 0 ||
			all->body->time_to_eat < 0 || all->body->time_to_sleep < 0 ||
			all->body->required_meals < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}*/

void	parse_args(t_philos	*all, int argc, char **argv,int i)
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

int	init_philos(int argc, char **argv, t_philos	*all)
{
	int i;

	i = 0;
	all->body = malloc(sizeof(t_param));
	if (!all->body)
		return (EXIT_FAILURE);
	if (!(argc == 5 || argc == 6))
	{
		printf("Give me 4 or 5 arguments\n");
		return (EXIT_FAILURE);
	}
	all->numb_of_philos = ft_atoi((argv[1]));
	all->body = (t_param *)malloc(sizeof(t_param) * all->numb_of_philos);
	if (all->body == NULL)
		return (EXIT_FAILURE);
	all->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
										  all->numb_of_philos);
	while (i++ < all->numb_of_philos)
		pthread_mutex_init(all->fork, NULL);
	pthread_mutex_init(&all->write_text, NULL);
	i = 0;
	while (i < all->numb_of_philos)
		parse_args(all, argc, argv, i++);
	if (all->numb_of_philos < 1 || all->body->time_to_die < 0 ||
		all->body->time_to_eat < 0 || all->body->time_to_sleep < 0 ||
		all->body->required_meals < 0)
		return (EXIT_FAILURE);
	return (0);
}
