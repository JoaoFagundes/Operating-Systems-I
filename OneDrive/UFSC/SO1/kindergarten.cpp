#include <iostream>
#include <stdio.h>
#include <stdlib.h>
/* ... other includes ... */
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
// Nome do aluno: João Victor de Mello Fagundes

using namespace std;

/***
 * @brief sem_init:     this function initializes the semaphore given in the
 *                      parameters. If call is successful, the semaphore is then 
 *                      ready to execute other functions like sem_wait() and 
 *                      sem_post()
 * @param sem_t *sem:   semaphore to be initialized.
 * 
 * @param int pshared:  specifies if semaphore is shared between processes.
 *                      If the value is '0', the semaphore is NOT shared between
 *                      processes. Any positive value turns it shared between
 *                      processes.
 * 
 * @param int value:    number of threads that can simultaneously access the
 *                      region protected by the semaphore
 * 
 * @return:             returns '0' if the call is successful. In case of
 *                      returning '-1', the call was not successful and errno
 *                      is set.
 * /

/**
 * @brief sem_wait:     this function is called when a thread wants to enter a
 *                      critical region. This call decrements the value of the
 *                      semaphore given as parameter if the value is positive.
 *                      If the value is 0, this means that the semaphore is full
 *                      and the thread is moved to a queue waiting to be called
 *                      to enter the critical region.
 * 
 * @param sem_t *sem:   the semaphore whose thread is trying to lock.
 * 
 * @return:             returns 0 if successful. If not, returns -1. Also, in
 *                      case of fail, semaphore is not decreased and errno is set.
 * /

/**
 * @brief sem_post:     this function is called when a thread wants to leave a
 *                      critical region. This call increments the value of the
 *                      semaphore given as parameter. By doing so, it opens a
 *                      slot for any thread that was waiting on the semaphore
 *                      to execute the critical region.
 * 
 * @param sem_t *sem:   the semaphore whose thread is trying to unlock.
 * 
 * @return:             returns 0 if successful. If not, returns -1. Also, in
 *                      case of fail, semaphore is not increased and errno is set.
 * /

/**
 * @brief sem_destroy:  destroys the semaphore ppinted by the address given in
 *                      the parameter.
 * 
 * @param sem_t *sem:   semaphore to be destroyed.
 * 
 * @return:             returns 0 if successful. If not, returns -1. Also, in
 *                      case of fail, errno is set.
 * 
 * /

/**
 * @brief pthread_create:   this function starts a new thread in the proccess and
 *                          sets the new created thread to execute the function
 *                          pointed by the address given in the parameters.
 * 
 * @param pthread_t *thread:    thread to be started.
 * 
 * @param pthread_attr_t *attr: attribute to be shared by the main and new threads.
 * 
 * @param void start_routine(): address to a function that will be the first
 *                              thing executed by the thread.
 * 
 * @param void *arg:            arguments to be passed from the main thread to
 *                              the new thread.
 * 
 * @return:                     returns 0 if is successful. If not, returns an
 *                              number identifying the error.
 * /

/**
 * @brief pthread_join:         blocks the execution of the main thread until
 *                              the execution of the thread given in params
 *                              is finished.
 * 
 * @param pthread_t thread:     thread whose execution must finishes in order to
 *                              unblock the main thread.
 * 
 * @param void *value_ptr:      variable that will store the value returned by
 *                              the thread after it exits. Used NULL if no
 *                              return is expected.
 * /


/* declare whenever global variables you need to synchronize pthreads using 
posix semaphores */
sem_t basket;

void *child(void *void_ptr)
{
  unsigned short *childNum = (unsigned short *)void_ptr;
  bool hasBall = false;
  
  if (*childNum < 3)
    hasBall = true;
        
  for (unsigned short i=1; i<=5; i++) {
    cout << "Child " << *childNum << " wants to play with the ball for the " << i << "th time" << endl;
    /* if the child has no ball, need to take one from the basket if there is 
    one, or will wait until there is a ball in the basket */
    if (hasBall == false) {
       cout << " Child " << *childNum << " wants to take a ball from the basket" << endl;
       sem_wait(&basket);
       hasBall == true;
    }
    /* once the child has a ball, he/she starts to play */
    cout << "  Child " << *childNum << " is playing with the ball" << endl;
    sleep(1);
    
    cout << "  Child " << *childNum << " wants to leave the ball in the basket" << endl;

    /* when the child is tired of playing, he/she has to drop the ball into the 
    basket, if there is room for it (basket holds only 3 balls), or will wait 
    until another hild to take a ball */
    
    sem_post(&basket);
    hasBall = false;
    cout << " Child " << *childNum << " has droped the ball in the basket" << endl;
    
  }
  cout << "Child " << *childNum << " will no longer play" << endl;
  /* exit the thread*/
  
}

int main()
{
    cout << "The kindengarten is open" << endl;
    
    /* declare local variable, such as threads */
    pthread_t childs[7];
    int vector[7];
    
    for (int i = 0; i < 7; i++)
        vector[i] = i;

    /* init semaphores to synchronize the threads */
    sem_init(&basket, 0, 0);

    /* create 7 threads for the children, passing to each one a different number (child 0 to 6) */
    for (int i = 0; i < 7; i++) {
        pthread_create(&childs[i], NULL, child, (void *)& vector[i]);
    }
    
    /* wait for all children to finish */
    for (int i = 0; i < 7; i++)
        pthread_join(childs[i], NULL);
    
    cout << "The kindengarten is closed" << endl;
    return 0;
    
    /* Respostas das perguntas "para pensar":
        
        1) Os semáforos NÃO podem ser variáveis locais. Caso fossem, a região
        crítica não estaria protegida pois o fechamento de um semáforo por uma
        thread não fecharia o semáforo para outras threads em execução. 
        Sim, todas as threads terminam, uma vez que a thread principal realiza
        um join para cada thread filha e só após isso, escreve na tela que
        o Jardim de Infância está fechado.
        
        2) O programa entraria em deadlock, pois agora o cesto só armazena uma
        bola. Como inicialmente temos três bolas, com três crianças distintas,
        sempre que uma criança fosse guardar a bola, caso o cesto já estivesse
        com uma bola, ela teria que aguardar. Se 5 crianças cansarem de brincar,
        duas estarão com uma bola cada uma e o cesto com uma bola. Quando a 6ª
        criança cansasse de brincar, ia guardar a bola no cesto já cheio. Ela
        então esperaria que alguma outra criança retirasse a bola do cesto para
        que ela pudesse guardar, o que nunca vai ocorrer pois as outras crianças
        já pararam de brincar. Poderia ser incluso um deadline ao programa.
        Assim, após o tempo estipulado de execução, o sistema pode perceber uma
        situação irregular e "matar" o processo pai, encerrando todas as threads.
    */
}
