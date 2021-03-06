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

#ifndef PHILO_B_H
# define PHILO_B_H

# include <string.h>	//memset
# include <stdio.h>		//printf
# include <stdlib.h>	//malloc free
# include <unistd.h>	//write usleep
# include <sys/time.h>	//gettimeofday
# include <pthread.h>	//pthread_create|detach
# include <semaphore.h>
# include <signal.h>

# define TAKE_FORK	"has taken a fork"
# define EAT		"is eating"
# define SLEEP		"is sleeping"
# define THINK		"is thinking"
# define DIE		"died"

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
	pthread_t		death;
	pid_t			pid;
	struct s_main	*all;
}				t_param;

typedef struct s_main{
	int				numb_of_philos;
	t_param			*body;
	sem_t			*fork_sem;
	sem_t			*write_sem;
	sem_t			*finish_sem;
	sem_t			*eat_sem;
	pthread_t		monit_eat;
}					t_philos;

int		ft_atoi(const char *str);

void	message(t_param *philo, const char *text);
int		life(t_param *philo);

int		init_philos(int argc, char **argv, t_philos *all);

void	*death(void *args);
void	*monit_eat(void *args);

int		error(char *msg);
long	get_time(void);
void	ft_msleep(long ms);

#endif
