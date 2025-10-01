/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:04:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 15:41:36 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

static void	start_philos(t_data *data)
{
	int		i;
	int		philo_id;
	t_philo	*philo;

	i = 0;
	philo_id = 1;
	philo = data->s_philo;
	while (i < data->total_philo)
	{
		philo[i].id = philo_id;
		philo[i].last_meal = data->start_time;
		philo[i].meals_eaten = 0;
		philo[i].eating = false;
		philo[i].max_meals = false;
		philo[i].r_fork = &data->forks[i];
		if (philo_id != data->total_forks)
			philo[i].l_fork = &data->forks[philo_id];
		else
			philo[i].l_fork = &data->forks[0];
		philo_id++;
		i++;
	}
}

bool	initialize_vars(int argc, char **argv)
{
	t_data	*data1;

	data()->total_philo = ft_atoi(argv[1]);
	data()->time_to_die = ft_atoi(argv[2]);
	data()->time_to_eat = ft_atoi(argv[3]);
	data()->time_to_sleep = ft_atoi(argv[4]);
	data()->meals_nb = 0;
	data()->meals_limiter = false;
	data()->total_forks = data()->total_philo;
	data()->start_time = get_time();
	data()->philo_died = false;
	if (argc == 6)
	{
		data()->meals_limiter = true;
		data()->meals_nb = ft_atoi(argv[5]);
	}
	data()->s_philo = malloc((sizeof(t_philo) * data()->total_philo));
	data()->forks = malloc(sizeof(pthread_mutex_t) * data()->total_forks);
	if (!data()->s_philo || !data()->forks)
		return (printf("failed to allocate memory"), false);
	data1 = data();
	start_philos(data1);
	return (true);
}

bool	check_args(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	create_thread(t_data *data1)
{
	int		i;
	int		j;
	t_philo	*philo;

	data()->start_time = get_time();
	data1 = data();
	philo = data1->s_philo;
	j = 0;
	while (j < data()->total_philo)
		philo[j++].last_meal = data()->start_time;
	i = -1;
	while (++i < data1->total_philo)
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (printf("erro ao criar thread"), clean_mem(data1), 0);
	usleep(100);
	if (pthread_create(&data1->monitor_thread, NULL, &monitoring, data1) != 0)
		return (printf("erro ao criar thread"), clean_mem(data1), 0);
	i = -1;
	while (++i < data1->total_philo)
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("erro  ao dar join na thread"), clean_mem(data1), 0);
	if (pthread_join(data1->monitor_thread, NULL) != 0)
		return (printf("erro  ao dar join na thread"), clean_mem(data1), 0);
	return (1);
}
