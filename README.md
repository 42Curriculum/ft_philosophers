# ft_philosophers

In this project we start learning about multithreading and parallel programming.

The goal is to make 3 programs that takes a number of philosophers and several other parameters. Each program differs in the way they handle threads and variables but they all follow the same rules :
<br> <img align="right" src=https://github.com/42Curriculum/ft_philosophers/blob/master/resources/philosophers.PNG/> <br>
```
• A number of philosophers are sitting at a round table doing one of three things:
eating, thinking or sleeping.
• While eating, they are not thinking or sleeping, while sleeping, they are not eating
or thinking and of course, while thinking, they are not eating or sleeping.
• The philosophers sit at a circular table with a large bowl of spaghetti in the center.
• There are some forks on the table.
• As spaghetti is difficult to serve and eat with a single fork, it is assumed that a
philosopher must eat with two forks, one for each hand.
• The philosophers must never be starving.
• Every philosopher needs to eat.
• Philosophers don’t speak with each other.
• Philosophers don’t know when another philosopher is about to die.
• Each time a philosopher has finished eating, he will drop his forks and start sleeping.
• When a philosopher is done sleeping, he will start thinking.
• The simulation stops when a philosopher dies.
```
## Philosophers one :

**Program name : p_one  or p_one_pairs**

 In this part, the program must use mutexes. Since the philosophers cannot talk to each other, this is the only way to pass information. I have two versions of this first exercise. One is the traditional way of solving this problem, one is a slighty improved way, using pair magic.

## Philosophers two :

**Program name : p_two**

Here, instead of using mutexes to pass information around, we are required to use a single named semaphore. Each philosopher is still a thread

## Philosophers three :

**Program name : p_three**

Much like philosophers two, we are also required to use a single semaphore to pass information around, but this time , each philsopher must be a process insted of a thread.

**This was made on WSL , using some libraries that are inexistant on windows and vary slightly on OSX, therefore there is a high chance the p_three and p_two won't work on these OSs.

## Usage

First, Make the program of your choice, then :

Usage : ./program_name [number] [time_to_die] [time_to_eat] [time_to_sleep] optional : [number_of_times_each_philosopher_must_eat]

**NOTE** : The operations might not appear in the right order , here Philosopher 0 seems to eat before he grabs a fork. However looking at the timestamp, one can see that both actions happened at the same instant, but one took longer to print, resulting in this weird offset

![](https://github.com/42Curriculum/ft_philosophers/blob/master/resources/theydied.PNG)
