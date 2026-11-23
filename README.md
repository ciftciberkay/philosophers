*This project has been created as part of the 42 curriculum by beciftci.*

# Philosophers

A simulation of the dining philosophers problem in C. Threads represent philosophers, and mutexes protect access to shared forks. The simulation tracks meals and monitors whether a philosopher runs out of time to eat.

## Build and run

From the repository root, use a C compiler and Make on a system with POSIX threads.

```sh
make -C philo
./philo/philo 5 800 200 200 3
```

The arguments are philosopher count, time to die, time to eat, time to sleep, and an optional meal count per philosopher. Times are in milliseconds. The example requests three meals per philosopher.

See [philo](./philo) for thread creation, timing, and simulation logic.
