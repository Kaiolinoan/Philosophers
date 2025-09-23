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
	bool			eating;
	bool			max_meals;
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
	int				meals_nb;
	bool			meals_limiter;
	bool			philo_died;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	t_philo			*s_philo;
	pthread_t		monitor;
}					t_data;

// libft functions
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_strlen(char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);


t_data				*data(void);
bool				initialize_vars(int argc, char **argv);
void				start_philos(t_data *data);
bool				check_args(int argc, char **argv);
void				*monitoring();
void				*routine();
int					create_thread(t_data *data);


// mutex
bool				intialize_mutex(t_data *data);
bool				destroy_mutex(t_data *data);

// utils
long				get_time(void);
void				print_msg(int id, char *msg);
void 				clean_mem(t_data *data);


// fork
void				take_left_fork(t_philo *philo);
void				take_right_fork(t_philo *philo);

#endif