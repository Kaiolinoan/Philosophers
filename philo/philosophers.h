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
	int				last_meal;
	int				meals_eaten;
	pthread_t		thread;
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
	long			start_time;
	int				min_meals;
	int				p_i;
	bool			minimun_meals;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	t_philo			*s_philo;
}					t_data;

// libft functions
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strlen(char *str);

t_data				*data(void);
bool				initialize_vars(char **argv);
void				start_philos(t_data *data);
bool				check_args(int argc, char **argv);

// mutex
bool				intialize_mutex(t_data *data);
bool				destroy_mutex(t_data *data);

// utils
long				get_time(void);
void				print_msg(int id, char *msg);

// fork
void				take_left_fork(t_philo *philo);
void				take_right_fork(t_philo *philo);

#endif