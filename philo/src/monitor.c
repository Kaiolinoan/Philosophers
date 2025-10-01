/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:37:11 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/01 16:58:10 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static bool	check_death_and_meals(int i)
{
	long	time;
	long	last;
	bool	is_eating;
	int		meals_eaten;

	pthread_mutex_lock(&data()->s_philo[i].meal_mutex);
	time = get_time();
	last = data()->s_philo[i].last_meal;
	is_eating = data()->s_philo[i].eating;
	meals_eaten = data()->s_philo[i].meals_eaten;
	pthread_mutex_unlock(&data()->s_philo[i].meal_mutex);
	if ((time - last > data()->time_to_die) && (!is_eating))
	{
		pthread_mutex_lock(&data()->state_mutex);
		data()->philo_died = true;
		pthread_mutex_unlock(&data()->state_mutex);
		return (print_msg(data()->s_philo[i].id, "died"), false);
	}
	if (data()->meals_limiter && meals_eaten == data()->meals_nb)
	{
		pthread_mutex_lock(&data()->s_philo[i].meal_mutex);
		data()->s_philo[i].max_meals = true;
		pthread_mutex_unlock(&data()->s_philo[i].meal_mutex);
	}
	return (true);
}

static bool	check_all_philos_ate(t_data *data)
{
	int		j;
	int		done;

	j = 0;
	done = 0;
	while (j < data->total_philo)
	{
		pthread_mutex_lock(&data->s_philo[j].meal_mutex);
		if (data->s_philo[j].max_meals)
			done++;
		pthread_mutex_unlock(&data->s_philo[j].meal_mutex);
		j++;
	}
	if (done == data->total_philo)
		return (true);
	return (false);
}

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;

	data = arg;
	while (1)
	{
		i = 0;
		while (i < data->total_philo)
			if (!check_death_and_meals(i++))
				return (NULL);
		if (data->meals_limiter && check_all_philos_ate(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
