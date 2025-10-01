/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:18:31 by klino-an          #+#    #+#             */
/*   Updated: 2025/09/17 17:29:12 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			sec;
	long			micro;
	long			mili;

	if (gettimeofday(&tv, NULL) < 0)
		return (printf("time failed"), 0);
	sec = tv.tv_sec * 1000L;
	micro = tv.tv_usec / 1000L;
	mili = sec + micro;
	return (mili);
}

void	print_msg(int id, char *msg)
{
	long	time;
	bool	is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	pthread_mutex_lock(&data()->mutex);
	time = get_time();
	time = time - data()->start_time;
	if (!is_dead || ft_strncmp(msg, "died", 4) == 0)
		printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&data()->mutex);
}

void	clean_mem(t_data *data)
{
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->s_philo)
	{
		free(data->s_philo);
		data->s_philo = NULL;
	}
}
