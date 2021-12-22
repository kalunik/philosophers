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

long get_time(void)
{
	struct timeval	tp;
	long			ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

//void	*philo_life(void	*arg)
//{
//	t_philos	*all;
//
//	all = arg;
//
//	//pthread_mutex_init(&all->body->write_text, NULL);
//	for (int i = 0; i < all->body->time_to_eat; i++)
//	{
//		//pthread_mutex_lock(&all->body->write_text);
//		printf("fdsmjfg");
//		//printf("[%d]	%d -- eating\n", i, all->body->numb_of_philos);
//		//pthread_mutex_unlock(&all->body->write_text);
//	}
//	return NULL;
//}



int	main(int argc, char **argv)
{
	int			i;
	t_philos	all;

//	if(parse_args(argc, argv, &all) == EXIT_FAILURE)
//		return (EXIT_FAILURE);
	init_philos(argc, argv, &all);

//	i = 0;
//	while (i < all.numb_of_philos)
//	{
//		printf("%d %d\n", all.body[i].l_fork, all.body[i].r_fork);
//		i++;
//	}
	return (0);
}


