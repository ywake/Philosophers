#ifndef MY_SEMAPHORE_H
# define MY_SEMAPHORE_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define FORKS_SEM ("/forks")
# define FINS_SEM ("/num_of_finish_philos")
# define LIVES_SEM ("/num_of_living_philos")
# define PRINT_SEM ("/printf")

#endif
