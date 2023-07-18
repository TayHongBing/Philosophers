/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:05:47 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/18 17:47:44 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	data->philo_count = ft_atoi(argv[1]);
	data->death_t = ft_atoi(argv[2]);
	data->eat_t = ft_atoi(argv[3]);
	data->sleep_t = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_count = ft_atoi(argv[5]);
	else
		data->meals_count = -1;
	if (data->philo_count <= 0 || data->death_t < 0
		|| data->eat_t < 0 || data->sleep_t < 0)
		return (p_err("INVALID INPUT", NULL));
	data->dead = 0;
	data->fin = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_count);
	if (!data->tid)
		return (p_err("ERR WITH TID", data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (p_err("ERR WITH FORKS", data));
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
		return (p_err("ERR WITH PHILO", data));
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philo[0].l_fork = &data->forks[0];
	data->philo[0].r_fork = &data->forks[data->philo_count - 1];
	i = 1;
	while (i < data->philo_count)
	{
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].t2d = data->death_t;
		data->philo[i].eat_cont = 0;
		data->philo[i].eating = 0;
		data->philo[i].status = 0;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
}

int	init(t_data *data, char **argv, int argc)
{
	if (init_data(data, argv, argc))
		return (1);
	if (alloc(data))
		return (1);
	if (init_forks(data))
		return (1);
	init_philo(data);
	return (0);
}