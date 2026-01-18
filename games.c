#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
pid_t p[16];
sem_t lock;
void clearScreen() {
    system("clear");
}

void *Chess(void *arg){
    sem_wait(&lock);
    p[0]=fork();
    if(p[0]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./chess.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *Guessgame(void *arg){
    sem_wait(&lock);
    p[1]=fork();
    if(p[1]==0){
     system("gnome-terminal -- /bin/bash -c 'g++ -o gg guessgame.cpp && ./gg; exec bash'");
    }
    else{
    	pthread_exit(NULL);
    }
}

void *Nibbles(void *arg){
    sem_wait(&lock);
    p[2]=fork();
    if(p[2]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./nibbles.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *Tictac(void *arg){
    sem_wait(&lock);
    p[4]=fork();
    if(p[4]==0){
    	system("gnome-terminal -- /bin/bash -c 'g++ -o tictac tictac.cpp && ./tictac; exec bash'");
    }
    else{
    	pthread_exit(NULL);
    }
}


int main(){
    int select = 0;
    sem_init(&lock,0,1);
    pthread_t threads[16];
    while (1) {
        clearScreen();
        printf("1) Chess\n");
        printf("2) Guessgame\n");
        printf("3) Tictac toe\n");
        printf("4) Nibbles\n");
	printf("Press any other key to exit Games.\n");
        printf("Enter your selection: ");
        scanf("%d", &select);
        switch (select) {
            case 1:
                pthread_create(&threads[0],NULL,Chess,NULL);
		sem_post(&lock);
                break;
            case 2:
                pthread_create(&threads[1],NULL,Guessgame,NULL);
		sem_post(&lock);
                break;
            case 3:
                pthread_create(&threads[2],NULL,Tictac,NULL);
		sem_post(&lock);
                break;
            case 4:
                pthread_create(&threads[3],NULL,Nibbles,NULL);
		sem_post(&lock);
                break;
            default:
		sem_destroy(&lock);
		return 0;
                break;
        }
    }
}
