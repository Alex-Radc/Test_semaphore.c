#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#ifdef _WIN32
    #include <conio.h>
    #include <Windows.h>
    #define Sleep(x) Sleep(x)
    #define wait() _getch()
#else
    #include <unistd.h>
    #define Sleep(x) sleep(x)
    #define wait() scanf("1")
#endif


sem_t semaphore1;
sem_t semaphore2;
sem_t semaphore3;
sem_t semaphore4;


static int counter = 0;

void* signaler1(void* args) {
	//sleep(3);
	sem_wait(&semaphore1);
    printf("signaler1 work!\n");
    printf("\n");
}

void* signaler2(void* args) {
	//sleep(1);
	sem_wait(&semaphore2);
    printf("signaler2 work!\n");
    sem_post(&semaphore1);
}
void* signaler3(void* args) {
	//sleep(3);
	sem_wait(&semaphore3);
	printf("signaler3 work!\n");
	sem_post(&semaphore2);
}
void* signaler4(void* args) {
	//sleep(3);
	sem_wait(&semaphore4);
    printf("signaler4 work!\n");
    sem_post(&semaphore3);
}

void* signaler5(void* args) {
    printf("signaler5 work!\n");
    sem_post(&semaphore4);
    //printf("\n");
}

void main(){
	int i = 0;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;

    sem_init(&semaphore1, 0, 0);
    sem_init(&semaphore2, 0, 0);
    sem_init(&semaphore3, 0, 0);
    sem_init(&semaphore4, 0, 0);

    for(i = 0; i<5; i++)
    {
    	pthread_create(&thread1, NULL, signaler1, NULL);
    	pthread_create(&thread2, NULL, signaler2, NULL);
    	pthread_create(&thread3, NULL, signaler3, NULL);
    	pthread_create(&thread4, NULL, signaler4, NULL);
    	pthread_create(&thread5, NULL, signaler5, NULL);


    	pthread_join(thread1, NULL);
    	pthread_join(thread2, NULL);
    	pthread_join(thread3, NULL);
    	pthread_join(thread4, NULL);
    	pthread_join(thread5, NULL);
    }
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    sem_destroy(&semaphore3);
    sem_destroy(&semaphore4);
    wait();
}
