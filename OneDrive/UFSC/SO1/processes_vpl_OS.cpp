#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
// nome do acadêmico: João Victor de Mello Fagundes
using namespace std;
int main ()
{
    // include declarations you need
    int count = 0; /*!< Global variable incremented by child processes */
    int i = 0; /*!< Iterator for the loop that creates the processes. */
    int parentPid = getpid(); /*!< Variable to store the PID of the parent process */
   
    /* Repeat 5 times */
    for (i; i < 5; i++) {
        if (getpid() == parentPid) {
            cout << "Parent process " << getpid() << ": Creating child" << endl;
            /* Duplicate this process */
            /// The fork() function creates a child process and both will execute the same code.
            fork();
            /* If there was an error on duplication then */
            if (errno == -1) {
                cout << "Error on fork()" << endl;
                return -1;
            /* If child-process is running then */
            } else if (getpid() != parentPid) {  
                cout << "Child process " << getpid() << ": Running" << endl;
                count++;
                /* Sleep for 1 second */
                sleep(1);
                cout << "Child process " << getpid() << ": Exiting with status " << count << endl;
            }
        }
    }
   
    /* if this is the parent-process then */
    if (parentPid == getpid()) {
        cout << "Parent process " << parentPid << ": Waiting children to exit" << endl;
        int errno, status, sum = 0;
        /* Parent-process waits for all children to exit, adding each status to the sum variable */


        /// The waitpid() function lets the calling process obtain status information about one of its child processes.
        /*!
            \param Specifies a set of child processes for which the status is requested.
                if is -1, status is requested for any child process.
            \param Specifies the location to which the child process' exit status is store.
            \param Is the bitwise inclusive-OR of zero or more of the following flags, defined in <sys/wait.h>
            \return If waitpid() was invoked with WNOHANG set in options, and there are children specified by 
                pid for which status is not available, waitpid() returns 0. If WNOHANG was not set, waitpid() 
                returns the process ID of a child when the status of that child is available. Otherwise, it returns -1
        */
        while (int pid = waitpid(-1, &status, 0)) {
            if (errno == ECHILD) {
                break;
            } else {
                /*! 
                  If the value of WIFEXITED(status) is non-zero, this macro evaluates to the low-order 
                  8 bits of the status argument that the child process passed to _exit() or exit(), or 
                  the value the child process returned from main().
                */
                sum += WEXITSTATUS(status);
            }
        }
        cout << "Parent process " << parentPid << ": Exiting with sum " <<sum << endl;
    }
   /*! 'return' used so the parent process can receive a value from child processes */
    return count;
  
  /* Respostas do "Para pensar e responder junto ao código:"
   1) 5.
   2) Não, pois cada processo vai ter sua própria variável, sem alterar o valor das variáveis nos outros processos.
   3) Os valores dos endereços serão iguais, pois o endereço que é mostrado na tela será o endereço virtual da variável,
      que é sempre igual antes, durante e após o fork. O que diferencia é o endereço real na memória.

  */

}  