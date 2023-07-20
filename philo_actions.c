/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:02:10 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/21 00:15:53 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(char *str, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_t;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

int	ft_sleep(useconds_t time)
{
	unsigned int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	message("has taken a fork", philo);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	message("is sleeping", philo);
	ft_sleep(philo->data->sleep_t);
}

void	eat(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->t2d = get_time() + philo->data->death_t;
	message("is eating", philo);
	philo->eat_cnt++;
	ft_sleep(philo->data->eat_t);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_fork(philo);
}
