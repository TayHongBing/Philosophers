/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:34:31 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/20 14:06:01 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

int	p_error(char *str, t_data *data)
{
	printf("s\n", str);
	if (data)
		ft_free(data);
	return (1);
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (p_error("INVALID INPUT", NULL));
			j++;
		}
		i++;
	}
	return (0);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (p_error("gettime error\n", NULL));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	one_philo(t_data *data)
{
	data->start_t = get_time();
	if (pthread_create(&data->tid[0], NULL, &routine, &data->philo[0]))
		return (p_error("THREAD ERROR", data));
	pthread_detach(data->tid[0]);
	while (data->dead == 0)
		ft_sleep(0);
	ft_free(data);
	return (0);
}
