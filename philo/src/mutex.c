/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:58:09 by klino-an          #+#    #+#             */
/*   Updated: 2025/09/17 15:13:14 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	intialize_mutex(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->state_mutex, NULL) != 0)
		return (false);
	while (i < data->total_forks)
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (false);
	while (j < data->total_philo)
		if (pthread_mutex_init(&data->s_philo[j++].meal_mutex, NULL) != 0)
			return (false);
	return (true);
}

bool	destroy_mutex(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (pthread_mutex_destroy(&data->mutex) != 0)
		return (false);
	if (pthread_mutex_destroy(&data->state_mutex) != 0)
		return (false);
	while (i < data->total_forks)
		if (pthread_mutex_destroy(&data->forks[i++]) != 0)
			return (false);
	while (j < data->total_philo)
		if (pthread_mutex_destroy(&data->s_philo[j++].meal_mutex) != 0)
			return (false);
	return (true);
}
