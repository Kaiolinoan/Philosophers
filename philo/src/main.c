/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:35:47 by marvin            #+#    #+#             */
/*   Updated: 2025/09/22 16:00:35 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

///

	// pthread_mutex_lock(&data->mutex);
	// 	while (j < data->total_philo)
	// 	{
	// 		printf("---philo[%d]---\n",j );
	// 		printf("id: %d\n", data->s_philo[j].id);
	// 		printf("last meal: %d\n", data->s_philo[j].last_meal);
	// 		printf("meals eaten: %d\n", data->s_philo[j].meals_eaten);
	// 		printf("l_fork: %p\n", &data->s_philo[j].l_fork);
	// 		printf("r_fork: %p\n", &data->s_philo[j].r_fork);
	// 		printf("\n");
	// 		j++;
	// 	}
	// 	pthread_mutex_unlock(&data->mutex);

///

void	take_left_fork(t_philo *philo)
{
	if (data()->philo_died == false)
	{
		print_msg(philo->id, "has taken a left fork");
		pthread_mutex_lock(philo->l_fork);
	}
}

void	take_right_fork(t_philo *philo)
{
	if (data()->philo_died == false)
	{
		print_msg(philo->id, "has taken a right fork");
		pthread_mutex_lock(philo->r_fork);
	}
}

void	philo_eat(t_philo *philo)
{
	if (data()->philo_died == false)
	{
		print_msg(philo->id,"is eating");
		philo->eating = true;
		usleep(data()->time_to_eat * 1000);
		philo->last_meal = get_time();
		philo->meals_eaten++;
		philo->eating = false;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (data()->philo_died == false)
	{
		print_msg(philo->id,"is sleeping");
		usleep(data()->time_to_sleep * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	if (data()->philo_died == false)
	{	
		print_msg(philo->id,"is thinking");
		usleep(100);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (data()->philo_died == false)
	{
		philo_think(philo);
		take_left_fork(philo);
		take_right_fork(philo);
		philo_eat(philo);
		if (philo->max_meals)
			break;
		philo_sleep(philo);
	}
	return (NULL);
}

void	*monitoring()
{
	int	i;

	i = 0;
	while(1)
	{
		long time = get_time();
		long last = data()->s_philo[i].last_meal;
		if (time - last >= data()->time_to_die)
			if (data()->s_philo[i].eating == false)
			{
				data()->philo_died = true;
				print_msg(data()->s_philo[i].id, "died");
				break;
			}
		if (data()->meals_limiter == true)
			if (data()->s_philo[i].meals_eaten == data()->meals_nb)
			{
				data()->s_philo[i].max_meals = true;	
				break;
			}
		i++;
		if (i == data()->total_philo)
			i = 0;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data1;

	data1 = NULL;
	if (argc > 6)
		return (printf("saiu no argc"), 0); // arumar aqui dps
	if (initialize_vars(argc, argv) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	data1 = data();
	if (check_args(argc, argv) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	if (intialize_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	start_philos(data1);
	if (create_thread(data1) == 0)
		return (0);
	if (destroy_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	clean_mem(data1);
}
