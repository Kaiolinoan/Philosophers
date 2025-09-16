/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:35:47 by marvin            #+#    #+#             */
/*   Updated: 2025/09/10 15:35:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"



void *routine(void *arg)
{
	int i = *(int *)arg;
	while(1)
	{
		take_left_fork();
		take_right_fork();
		//pegar o garfo
		//comer
		//dormir
		//pensar
		//morrer 
	}
	return NULL;
}

int	main(int argc, char **argv)
{
	t_philo		*data;
	int			i;

	data = NULL;
	if (argc > 6)
		return (printf("saiu no argc"), 0); //arumar aqui dps
	data = initialize_vars(argc, argv);
    if (!data)
		return (free(data->philos), EXIT_FAILURE);
	if (check_args(argc, argv) == false)
		return (EXIT_FAILURE); //dps verificar se aloquei alguma coisa antes de sair
	// pthread_mutex_init(data->mutex, NULL);
	i = -1;
	while (++i < data->total_philo)
	{
		int *sla = malloc(sizeof(int));
		*sla = i;
		if (pthread_create(&data->philos[i], NULL, &routine, sla) < 0) //criar routine
			return (printf("erro ao criar thread"), 0);
	}
	i = -1;
	while (++i < data->total_philo)
		if (pthread_join(data->philos[i], NULL) != 0) //criar routine
			return (printf("erro ao criar thread"), 0);
	// pthread_mutex_destroy(data()->mutex);
}
