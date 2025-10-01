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

int	main(int argc, char **argv)
{
	t_data	*data1;

	data1 = NULL;
	if (argc > 6 || argc < 5)
		return (printf("Invalid input"), 0);
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
