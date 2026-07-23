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
* https://sites.uclouvain.be/SyllabusC/notes/Theorie/Threads/threads2.html
* https://cs.ip-paris.fr/courses/chps/paam/?page=all&wrap=true&preprint=true
* https://blog.gistre.epita.fr/posts/odric.roux-paris-2023-01-31/
* https://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/
* https://docs.dennisokeeffe.com/comp3520-os/pthread
* https://members.loria.fr/lnussbaum/RS/CM-ch6-nup.pdf

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




# CPU time vs real-time clock

...

## second, microsecond, nanosecond

* 200 millisecond == 200000 microseconds.
* 200 millisecond == 200000000 nano seconde

Les contrainte de temps: time_to_burnout, time_to_compile, time_to_debug,
time_to_refactor, dongle_cooldown sont exprimees en milliseconde.

La fonction usleep elle prend en parametre des micro seconde no contrainte doivent donc etre convertie en microseconde: *contrainte* * 1000

### mesure du temps

#### clock_gettime

La fonction clock_gettime() prend en argument une resolution  (CLOCK_REALTIME, CLOCK_THREAD_CPUTIME_ID...) et un pointeur vers une structure  struct timespec 

```c
 struct timespec 
{
    time_t  tv_sec;  /* Seconds */
    long    tv_nsec; /* Nanoseconds */
};

clock_gettime(CLOCK_REALTIME, &timespec)

```
Pour etablire le temps ecouler en milliseconde depuis un apelle de reference a  clock_gettime if faut apliquer la fomule suivente:

(temps_de_reference_2(en nanoseconde) - temps_de_reference_1(en nanoseconde)) / 1000000

#### gettimeofday

# lldb

## Launch process codexion with arguments 10 200 100 100 100 10 100 fifo  by setting the args in the debugger

settings set target.run-args 10 200 100 100 100 10 100 fifo

## Set a breakpoint in file *<name_file>* at line *<line_number>*

breakpoint set --file *<name_file>* --line *<line_number>*