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



// void	take_left_fork(t_philo *philo)
// {
// 	bool is_dead;

// 	pthread_mutex_lock(&data()->state_mutex);
// 	is_dead = data()->philo_died;
// 	pthread_mutex_unlock(&data()->state_mutex);
// 	if (!is_dead)
// 	{
// 		pthread_mutex_lock(philo->l_fork);
// 		print_msg(philo->id, "has taken a left fork");
// 	}
// }

// void	take_right_fork(t_philo *philo)
// {
// 	bool is_dead;

// 	pthread_mutex_lock(&data()->state_mutex);
// 	is_dead = data()->philo_died;
// 	pthread_mutex_unlock(&data()->state_mutex);
// 	if (!is_dead)
// 	{
// 		pthread_mutex_lock(philo->r_fork);
// 		print_msg(philo->id, "has taken a right fork");
// 	}
// }

void	philo_eat(t_philo *philo)
{
	bool is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eating = true;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!is_dead)
	print_msg(philo->id,"is eating");
	usleep(data()->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_sleep(t_philo *philo)
{
	bool is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	if (!is_dead)
	{
		print_msg(philo->id,"is sleeping");
		usleep(data()->time_to_sleep * 1000);
	}
}

void	philo_think(t_philo *philo)
{
	bool is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	if (!is_dead)
	{	
		print_msg(philo->id,"is thinking");
		usleep(data()->time_to_eat * 1000);
	}
}

void	choose_fork(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->id % 2 != 0)
	{
		first = philo->l_fork;
		second = philo->r_fork;
	}
	else 
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}

	pthread_mutex_lock(first);
	print_msg(philo->id, "has taken a fork");
	pthread_mutex_lock(second);
	print_msg(philo->id, "has taken a fork");
}

// void choose_fork(t_philo *philo)
// {
//     pthread_mutex_t *first;
//     pthread_mutex_t *second;

//     if (philo->id == data()->total_philo) // último filósofo
//     {
//         first = philo->r_fork;
//         second = philo->l_fork;
//     }
//     else
//     {
//         first = philo->l_fork;
//         second = philo->r_fork;
//     }

//     pthread_mutex_lock(first);
//     print_msg(philo->id, "has taken a fork");
//     pthread_mutex_lock(second);
//     print_msg(philo->id, "has taken a fork");
// }

void	*routine(void *arg)
{
	t_philo *philo;
	bool is_dead;
	philo = arg;

	if (philo->id % 2 == 0)
 	   usleep(data()->time_to_eat * 1000);

	while (1)
	{
		pthread_mutex_lock(&data()->state_mutex);
		is_dead = data()->philo_died;
		pthread_mutex_unlock(&data()->state_mutex);
		if (philo->max_meals || is_dead)
			break;
		choose_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*monitoring()
{
	int	i;

	i = 0;
	while(1)
	{
		i = 0;
		while (i < data()->total_philo)
		{
			pthread_mutex_lock(&data()->s_philo[i].meal_mutex);
			long time = get_time();
			long last = data()->s_philo[i].last_meal;
			bool is_eating = data()->s_philo[i].eating;
			int meals_eaten = data()->s_philo[i].meals_eaten;
			pthread_mutex_unlock(&data()->s_philo[i].meal_mutex);
			if ((time - last > data()->time_to_die) &&  (!is_eating))
			{
				pthread_mutex_lock(&data()->state_mutex);
				data()->philo_died = true;
				pthread_mutex_unlock(&data()->state_mutex);
				print_msg(data()->s_philo[i].id, "died");
				return (NULL);
			}
			if (data()->meals_limiter && meals_eaten == data()->meals_nb)
			{
				pthread_mutex_lock(&data()->s_philo[i].meal_mutex);
				data()->s_philo[i].max_meals = true;
				pthread_mutex_unlock(&data()->s_philo[i].meal_mutex);
			}
			i++;
		}
		if (data()->meals_limiter)
		{
			int done;
			int j;

			done = 0;
			j = 0;
			while (j < data()->total_philo)
			{
				pthread_mutex_lock(&data()->s_philo[j].meal_mutex);
				if (data()->s_philo[j].max_meals)
					done++;
				pthread_mutex_unlock(&data()->s_philo[j].meal_mutex);
				j++;
			}
			if (done == data()->total_philo)
				return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data1;

	data1 = NULL;
	if (argc > 6 || argc < 5)
		return (printf("saiu no argc"), 0); // arumar aqui dps
	if (initialize_vars(argc, argv) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	data1 = data();
	if (check_args(argc, argv) == false)
		return (clean_mem(data1), EXIT_FAILURE);	
	if (intialize_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	if (create_thread(data1) == 0)
		return (0);
	if (destroy_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	clean_mem(data1);
}
