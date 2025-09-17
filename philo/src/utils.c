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

	if (gettimeofday(&tv, NULL) < 0 )
		return ( printf("time failed"),0);
	sec = tv.tv_sec * 1000L;
	micro = tv.tv_usec / 1000L;
	mili = sec + micro;
	return (mili);
}

void	print_msg(int id, char *msg)
{
	long	time;

	time = get_time();
	time = time - data()->start_time;
	// write(1, &time, sizeof(time));
	// write(1, " ", 1);
	// write(1, &id, sizeof(id));
	// write(1, " ", 1);
	// write(1, msg, ft_strlen(msg));
	printf("%ld %d %s \n", time, id, msg);
}
