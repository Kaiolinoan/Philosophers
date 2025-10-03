/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:33:39 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/02 16:49:12 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	philo_eat(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eating = true;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!is_dead)
		print_msg(philo->id, "is eating");
	usleep(data()->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	philo->eating = false;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	philo_sleep(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	if (!is_dead)
	{
		print_msg(philo->id, "is sleeping");
		usleep(data()->time_to_sleep * 1000);
	}
}

static void	philo_think(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(&data()->state_mutex);
	is_dead = data()->philo_died;
	pthread_mutex_unlock(&data()->state_mutex);
	if (!is_dead)
	{
		print_msg(philo->id, "is thinking");
		usleep(500);
	}
}

static bool	choose_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

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
	if (data()->total_philo == 1)
		return (pthread_mutex_unlock(first), false);
	pthread_mutex_lock(second);
	print_msg(philo->id, "has taken a fork");
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	bool	is_dead;
	bool	max_meals;

	philo = arg;
	if (data()->meals_nb == 0 && data()->meals_limiter)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&data()->state_mutex);
		is_dead = data()->philo_died;
		pthread_mutex_unlock(&data()->state_mutex);
		pthread_mutex_lock(&philo->meal_mutex);
		max_meals = philo->max_meals;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (max_meals || is_dead)
			break ;
		if (!choose_fork(philo))
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
