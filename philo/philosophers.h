#ifndef PHILOSOPHERS_H
#define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philosophers
{
	int				argc;
	char			**argv;
	int				total_philo;
	int				total_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_meals;
	bool			minimun_meals;
	pthread_mutex_t	*mutex;
	pthread_t		*philos;
	int				*forks;
}	t_philo;


t_philo	*initialize_vars(int argc, char **argv);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
bool	check_args(int argc, char **argv);
t_philo	*data(void);



#endif 