# Philosophers
[![Norminette](https://github.com/ywake/Philosophers/actions/workflows/norm.yml/badge.svg)](https://github.com/ywake/Philosophers/actions/workflows/norm.yml)

## philo
### Build
```bash
cd philo
make
```

### Run
```bash
./philo 10 210 100 100 3
```

#### Arg
1. number_of_philosophers
1. time_to_die
1. time_to_eat
1. time_to_sleep
1. (option) number_of_times_each_philosopher_must_eat

## philo_bonus
### Build
```bash
cd philo_bonus
make
```

### Run
```bash
./philo_bonus 10 210 100 100 3
```

#### Arg
1. number_of_philosophers
1. time_to_die
1. time_to_eat
1. time_to_sleep
1. (option) number_of_times_each_philosopher_must_eat

### Test
The buffered output will be discarded because the process is terminated by kill.  
So, add the following code somewhere and set it to not do buffering.
```c
setbuf(stdout, NULL);
```
Testing
```bash
./philo_bonus ... | grep eat | wc -l
```
