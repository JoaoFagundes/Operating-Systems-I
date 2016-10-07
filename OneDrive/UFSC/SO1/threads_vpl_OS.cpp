#include <iostream>
#include <pthread.h>
//nome do aluno: João Victor de Mello Fagundes


using namespace std;

pthread_mutex_t mymutex;

void *inc_(void *void_ptr)
{   
	/* increment x to 100 */
	int *ptr = (int *)void_ptr;
	int i=0;
	for (i; i<100; i++) 
	{
		/* enter critical region */
		pthread_mutex_lock(&mymutex);
		++(*ptr);
		/* leave critical region */
		pthread_mutex_unlock(&mymutex);
	}
	cout << "increment finished" << endl;
	return NULL;
}

void *dec_(void *void_ptr)
{
    /* decrement x to 100 */
    int *ptr = (int *)void_ptr;
	int i=0;
	for (i; i<100; i++)
	{
		/* enter critical region */
		pthread_mutex_lock(&mymutex);
		--(*ptr);
		/* leave critical region */
		pthread_mutex_unlock(&mymutex);
	}        
    cout << "decrement finished" << endl;
    return NULL;
}


int main()
{
	int x = 0;
	cout << "x: " << x << endl;

	/* declare threads */ 
	
	pthread_t inc_thread, dec_thread;
	
	/* init mutexex */
    
    pthread_mutex_init(&mymutex, NULL);
    
    /* create a first thread which executes inc_(&x) */
    
    pthread_create(&inc_thread, NULL, inc_, (void *) &x);

	/* create a second thread which executes dec_(&x) */
	
	pthread_create(&dec_thread, NULL, dec_, (void *) &x);

    /* wait for the first thread to finish */
    
    pthread_join(inc_thread, NULL);

	/* wait for the second thread to finish */
	
	pthread_join(dec_thread, NULL);

	/* destroy miutex */
	
	pthread_mutex_destroy(&mymutex);

	cout << "x: " << x << endl;
	return 0;
}

/* Respostas do "Para pensar e responder junto ao código:"
   Cada variável 'count' era incrementada apenas no seu processo, não alterando
   o valor das cópias da variável 'count' dos outros processos. O mesmo não vai
   acontecer aqui pois as threads compartilham o espaço de enderaçamento, ou
   seja, ao alterar o valor de uma variável global em uma thread, o valor é 
   alterado para todas. O valor esperado da variável count é '0'. Se não houver
   a proteção contra a condição de corrida, através do mutex por exemplo,
   não podemos afirmar com certeza qual seria o valor de 'x', podendo assumir
   qualquer valor entre -100 e 100.
*/