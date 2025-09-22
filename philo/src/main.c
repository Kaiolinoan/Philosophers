/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:35:47 by marvin            #+#    #+#             */
/*   Updated: 2025/09/17 17:41:51 by klino-an         ###   ########.fr       */
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
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo->id, "has taken a left fork");
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo->id, "has taken a right fork");
}

void	philo_eat(t_philo *philo)
{
	print_msg(philo->id,"is eating");
	usleep(data()->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_msg(philo->id,"is sleeping");
	usleep(data()->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_msg(philo->id,"is thinking");
	usleep(100);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		philo_think(philo);
		//pode dar deadlock, entao mudar a ordem cpa
		take_left_fork(philo);
		take_right_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		// morrer
		break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data1;

	int i = -1;
	if (argc > 6)
		return (printf("saiu no argc"), 0); // arumar aqui dps
	if (initialize_vars(argv) == false)
		return (free(data()->forks), free(data()->s_philo), EXIT_FAILURE);
	data1 = data();
	if (check_args(argc, argv) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	if (intialize_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	start_philos(data1);
	while (++i < data1->total_philo)
		if (pthread_create(&data1->s_philo[i].thread, NULL, &routine, &data1->s_philo[i]) < 0)
			return (printf("erro ao criar thread"), clean_mem(data1), 0);
	i = -1;
	while (++i < data1->total_philo)
		if (pthread_join(data1->s_philo[i].thread, NULL) != 0)
			return (printf("erro  ao dar join na thread"), clean_mem(data1) ,0);
	if (destroy_mutex(data1) == false)
		return (clean_mem(data1), EXIT_FAILURE);
	clean_mem(data1);
}
