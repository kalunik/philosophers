/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:17 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

int		error(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

long	get_time(void)
{
	struct timeval	tp;
	long			ms;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000;
	ms += tp.tv_usec / 1000;
	return (ms);
}

void	ft_msleep(long ms)
{
	long	begin;

	begin = get_time();
	usleep(ms * 920);
	while (get_time() < begin + ms)
		usleep(ms * 3);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
//
//void	end_threads(t_philos	*all)
//{
//	int	i;
//
//	i = 0;
//	while (i < all->numb_of_philos)
//	{
//		pthread_mutex_destroy(&all->fork[i]);
//		i++;
//	}
//	pthread_mutex_destroy(&all->write_text);
//	free(all->body);
//	free(all->fork);
//	free(all);
//}
