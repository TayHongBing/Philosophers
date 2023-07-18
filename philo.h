/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*`Created: 2023/07/14 16:05:23 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/18 15:54:40 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "./Libft/libft.h"

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_count;
	int				meals_count;
	int				dead;
	int				fin;
	t_philo			*philo;
	unsigned int	death_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	unsigned int	start_t;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	unsigned int	t2d;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

int	check_input(char **argv);
int	p_error(char *str, t_data *data);