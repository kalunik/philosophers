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

# define TAKE_FORK_L "has taken a fork L"
# define TAKE_FORK_R "has taken a fork R"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define TAKE_FORK_TEXT_SIZE 18
# define EAT_TEXT_SIZE 9
# define DIE_TEXT_SIZE 4
# define UNUSED_TEXT_SIZE 11

typedef struct s_args{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	long			last_eat;
	int				meal_counter;
	int				alive;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_text;
	pthread_t		philo_t;
}				t_param;

typedef struct s_main{
	pthread_mutex_t	*fork;
	pthread_mutex_t	write_text;
	int				numb_of_philos;
	t_param			*body;
}					t_philos;

long	get_time(void);

int		ft_atoi(const char *str);

int		init_philos(int argc, char **argv, t_philos *all);

#endif
