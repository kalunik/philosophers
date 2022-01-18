/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:59:17 by wjonatho          #+#    #+#             */
/*   Updated: 2021/12/02 18:08:54 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_b.h"

void	message(t_param *philo, const char *text)
{
	size_t	text_size;

	text_size = ft_strlen(text);

	//todo семафор на текст
	//pthread_mutex_lock(philo->write_text);
	printf("%p\n", &philo->all->write_sem);

	sem_wait(philo->all->write_sem);

	printf("%ld", get_time() - philo->start_time);
/*	if (text_size == TAKE_FORK_TEXT_SIZE)
		printf("\033[0;36m");
	else if (text_size == EAT_TEXT_SIZE)
		printf("\033[1;34m");
	else if (text_size == DIE_TEXT_SIZE)
		printf("\033[1;31m");*/
	printf(" %d %s\n", philo->id, text);
/*	if (text_size != UNUSED_TEXT_SIZE)
		printf("\033[0m");
	if (ft_strlen(text) != DIE_TEXT_SIZE)
		pthread_mutex_unlock(philo->write_text);*/
	sem_post(philo->all->write_sem);
	printf("dsfdfdsfds\n");
}
//
//void	eating(t_param	*philo)
//{
//	pthread_mutex_lock(philo->l_fork);
//	message(philo, TAKE_FORK_L);
//	pthread_mutex_lock(philo->r_fork);
//	message(philo, TAKE_FORK_R);
//	message(philo, EAT);
//	ft_msleep(philo->time_to_eat);
//	philo->last_eat = get_time();
//	if (philo->required_meals != -1)
//		philo->meal_counter++;
//	pthread_mutex_unlock(philo->l_fork);
//	pthread_mutex_unlock(philo->r_fork);
//}
//
//void	sleeping(t_param	*philo)
//{
//	message(philo, SLEEP);
//	ft_msleep(philo->time_to_sleep);
//}
//
void	thinking(t_param	*philo)
{
	message(philo, THINK);
}

int	life(t_param philo)
{
	printf("342345\n");
	//fixme проверить приходит ли структура правильно
	if (philo.id % 2 == 0)
		usleep(100); //todo посмотреть не опасно ли юзать, мона отправлятьспать
	while (philo.alive == 0)
	{
//		eating(philo);
//		sleeping(philo);
		thinking(&philo);
	}
	return (EXIT_FAILURE);
}
