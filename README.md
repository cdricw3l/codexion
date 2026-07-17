*This project has been created as part of the 42 curriculum by cebouhad*

# 🧑‍🏭 codexion

## Description

Juste test for seeing if the github setup work

## Instructions

To compile the library and generate the static library.

```bash
make
```
or

```bash
make codexion
```
or

```bash
make all
```
To delete all object files
```bash
make clean
```

To delete all object files and the static library:
```bash
make fclean
```

To delete all object files, the static library and compile the library:
```bash
make re
```

## Resources

* https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html


# Blocking cases handled

# Thread synchronization mechanisms

# notes and idees

for seeing the number max of thread for process: cat /proc/sys/kernel/threads-max


# autorized External Function

pthread_create
pthread_join
pthread_mutex_init,
pthread_mutex_lock,
pthread_mutex_unlock
pthread_mutex_destroy:
pthread_cond_init:
pthread_cond_wait
pthread_cond_timedwait:
pthread_cond_signal:
pthread_cond_broadcast:
pthread_cond_destroy:
gettimeofday:
clock_gettime


# lldb

## Launch process codexion with arguments 10 200 100 100 100 10 100 fifo  by setting the args in the debugger

settings set target.run-args 10 200 100 100 100 10 100 fifo

## Set a breakpoint in file *<name_file>* at line *<line_number>*

breakpoint set --file *<name_file>* --line *<line_number>*