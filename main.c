/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thong-bi <thong-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:04:47 by thong-bi          #+#    #+#             */
/*   Updated: 2023/07/19 11:20:44 by thong-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argv > 5 || argv > 6)
		return (1);
	if (check_input(argv))
		return (1);
	if (init(&data, argv, argc))
		return (1);
	if (data.philo_count == 1)
		return (one_philo(&data));
}