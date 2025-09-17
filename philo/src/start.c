/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:04:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/17 17:14:12 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_data	*data(void)
{
    static t_data data;
    return (&data); 
}

void start_philos(t_data *data)
{
    int i;
    int philo_id;
	t_philo *philo;
	
    i = 0;
    philo_id = 1;
	philo = data->s_philo;
    while (i < data->total_philo)
    {
        philo[i].id = philo_id;
        philo[i].last_meal = -1;
        philo[i].meals_eaten = -1;
        philo[i].r_fork = &data->forks[i];
        if (philo_id != data->total_forks)
           philo[i].l_fork = &data->forks[philo_id];
        else
           philo[i].l_fork = &data->forks[0];
		philo_id++;
		i++;
    }
}

bool	initialize_vars(char **argv)
{
	data()->total_philo = ft_atoi(argv[1]);
	data()->time_to_die = ft_atoi(argv[2]);
	data()->time_to_eat = ft_atoi(argv[3]);
	data()->time_to_sleep = ft_atoi(argv[4]);
	data()->minimun_meals = false;
	data()->total_forks = data()->total_philo;
	data()->start_time = get_time();
	data()->p_i = -1;
	if (argv[5])
	{
		data()->minimun_meals = true;
		data()->min_meals = ft_atoi(argv[5]);
	}
	data()->s_philo = malloc((sizeof(t_philo) * data()->total_philo));
    data()->forks = malloc(sizeof(pthread_mutex_t) * data()->total_forks);
	if (!data()->s_philo || !data()->forks)
		return (printf("failed to allocate memory"), false);
	return (true);
}

bool	check_args(int argc, char **argv)
{
    int	i;
    int	j;

	i = 1;
	while (i <= argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (false);
            if (argv[i][j] <= 0 )
            {
                if (argv[5][j] >= 0)
                    continue;
                else 
                    return (false);
            }
			j++;
		}
		i++;
	}
	return (true);
}
