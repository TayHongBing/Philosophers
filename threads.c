/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:22:25 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/20 15:37:40 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_meal(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) data_ptr;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %d", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->fin >= philo->data->philo_count)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*check_dead(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->t2d && philo->eating == 0)
			message("died", philo);
		if (philo->eat_cnt == philo->data->meals_count)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->fin++;
			philo->eat_cnt++;
			pthread_mutex_unlock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->t2d = philo->data->death_t + get_time();
	if (pthread_create(&philo->t1, NULL, &check_dead, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		message("is thinking", philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	init_thread(t_data *data)
{
	int			i;
	pthread_t	t;

	i = -1;
	data->start_t = get_time();
	if (data->meals_count > 0)
	{
		if (pthread_create(&t, NULL, &check_meal, &data->philo[0]))
			return (p_error("THREAD ERROR", data));
	}
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philo[i]))
			return (p_error("THREAD ERROR", data));
		ft_sleep(1);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(data->tid[i], NULL))
			return (p_error("JOIN ERROR", data));
	}
	return (0);
}
