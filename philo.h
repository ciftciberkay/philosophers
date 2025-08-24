#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int             id;             // filozof numarası (1’den başlar)
	int             meals_eaten;    // kaç defa yemek yedi
	long long       last_meal;      // en son yemek yediği zaman (ms)
	pthread_t       thread_id;      // filozofun thread’i
	struct s_data   *data;          // ortak veri yapısına erişim
	pthread_mutex_t *left_fork;     // solundaki çatal
	pthread_mutex_t *right_fork;    // sağındaki çatal
}   t_philo;

typedef struct s_data
{
	int       		nbr_philos;     // filozof sayısı
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;       // (opsiyonel) her filozofun yemesi gereken sayı
	int				finished;       // simülasyon bitiş flag
	long long		start_time;     // simülasyon başlangıcı
	pthread_mutex_t	*forks;         // her çatal için mutex array
	pthread_mutex_t	print_mutex;    // printf için mutex (karışmasın)
	t_philo         *philos;        // filozofların listesi
}   t_data;

long long	ft_atoll(const char *str);
int			ft_atoi(const char *str);
int         ft_isdigit(int c);

#endif