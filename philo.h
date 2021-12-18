/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:58:49 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 18:53:09 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc free
# include <unistd.h> //write usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h>//pthread_create|detach|join,mutex_init|destroy|lock|unlock


typedef struct s_args{
	int	id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	required_meals;
	int start_pr;
	int last_eat;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *write_text;

}				t_param;

typedef struct s_main{
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_text;
	int		numb_of_philos;
	t_param	*body;
}				t_philos;

int		ft_atoi(const char *str);

int parse_args(int argc, char **argv, t_philos *all);

#endif
