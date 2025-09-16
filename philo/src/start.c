/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:04:41 by marvin            #+#    #+#             */
/*   Updated: 2025/09/10 17:04:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philo	*data(void)
{
    static t_philo philo;
    return (&philo); 
}
t_philo	*initialize_vars(int argc, char **argv)
{
    t_philo *data;

    data = malloc(sizeof(t_philo));
    if (!data)
        return (NULL);
    data->argc = argc;
    data->argv = argv;
    data->total_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->minimun_meals = false;
    data->total_forks = data->total_philo;
    data->mutex = NULL;
    if (argv[5])
    {
        data->minimun_meals = true;
        data->min_meals = ft_atoi(argv[5]);
    }
    data->philos = malloc ((sizeof(pthread_t *) * ft_atoi(argv[1])) + 1);
    data->forks = malloc (sizeof(int) * ft_atoi(argv[1]));
    if (!data->philos || !data->forks)  
        return NULL ;
    return (data);
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
