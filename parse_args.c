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

void	null_to_param(t_param *body)
{
	body->numb_of_philos = 0;
	body->time_to_die = 0;
	body->time_to_eat = 0;
	body->time_to_sleep = 0;
	body->required_meals = 0;
}

void	parse_args(int argc, char **argv, t_philos	*all)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Give me 4 or 5 arguments\n");
		exit(EXIT_FAILURE);
	}
	null_to_param(all->body);
	printf("%d\n", all->body->time_to_eat);
	all->body->numb_of_philos = ft_atoi(argv[1]);
	all->body->time_to_die = ft_atoi(argv[2]);
	all->body->time_to_eat = ft_atoi(argv[3]);
	all->body->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->body->required_meals = ft_atoi(argv[5]);
}
