/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:22:14 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/01 15:22:14 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopers
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	bool			eating;
	bool			max_meals;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_data
{
	int				total_philo;
	int				total_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	long			start_time;
	bool			meals_limiter;
	bool			philo_died;
	pthread_t		monitor_thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	*forks;
	t_philo			*s_philo;
}					t_data;

// libft functions
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strlen(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

//start
t_data				*data(void);
bool				initialize_vars(int argc, char **argv);
bool				check_args(int argc, char **argv);
int					create_thread(t_data *data);

//general
void				*monitoring(void *arg);
void				*routine(void *arg);

// mutex
bool				intialize_mutex(t_data *data);
bool				destroy_mutex(t_data *data);

// utils
long				get_time(void);
void				print_msg(int id, char *msg);
void				clean_mem(t_data *data);

#endif