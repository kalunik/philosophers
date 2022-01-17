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
	all->body[i].l_fork = &all->fork[i];
	all->body[i].r_fork = &all->fork[(i + 1) % all->numb_of_philos];
	all->body[i].write_text = &all->write_text;
}

static inline int	validate_params(int argc, t_philos	*all)
{
	if (all->numb_of_philos < 1 || all->body->time_to_die < 0
		|| all->body->time_to_eat < 0 || all->body->time_to_sleep < 0
		|| (argc == 6 && all->body->required_meals < 0))
	{
		printf("Invalid args\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_philos(int argc, char **argv, t_philos	*all)
{
	int	i;

	if (!(argc == 5 || argc == 6))
	{
		printf("There should be 4 or 5 arguments\n");
		return (EXIT_FAILURE);
	}
	all->numb_of_philos = ft_atoi((argv[1]));
	all->body = (t_param *) malloc(sizeof(t_param) * all->numb_of_philos);
	if (all->body == NULL)
		return (EXIT_FAILURE);
	/// под семафор на кол-во вилок(филов)
	all->fork = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* all->numb_of_philos);
	i = 0;
	/// семафор один на печать
	pthread_mutex_init(&all->write_text, NULL);
	/// семафор на кол-во филов
	while (i < all->numb_of_philos)
	{
		pthread_mutex_init(&all->fork[i], NULL);
		parse_args(all, argc, argv, i++);
	}
	if (validate_params(argc, all))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
