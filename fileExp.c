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

void *OpenTask(void *arg){
    sem_wait(&lock);
    p[0]=fork();
    if(p[0]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./open.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *CopyFile(void *arg){
    sem_wait(&lock);
    p[1]=fork();
    if(p[1]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./cpyFile.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *CutFile(void *arg){
    sem_wait(&lock);
    p[2]=fork();
    if(p[2]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./mvFIle.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *CreateFolder(void *arg){
    sem_wait(&lock);
    p[4]=fork();
    if(p[4]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./mkFolder.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *ShowFiles(void *arg){
    sem_wait(&lock);
    p[5]=fork();
    if(p[5]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./showF.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *DelFiles(void *arg){
    sem_wait(&lock);
    p[6]=fork();
    if(p[6]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./rmFile.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
    }
    else{
    	pthread_exit(NULL);
    }
}

void *DelDir(void *arg){
    sem_wait(&lock);
    p[7]=fork();
    if(p[7]==0){
    	char *argv[] = {"gnome-terminal", "--disable-factory", "--", "./rmDir.sh", NULL};
	if (execvp(argv[0], argv) == -1) {
	    perror("Error in execvp");
    	}
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
        printf("1) Open File\n");
        printf("2) Copy File\n");
        printf("3) Cut File\n");
        printf("4) Create New Folder\n");
	printf("5) Show Files\n");
	printf("6) Delete File\n");
	printf("7) Delete Folder\n");
	printf("Press any other key to exit File Explorer.\n");
        printf("Enter your selection: ");
        scanf("%d", &select);
        switch (select) {
            case 1:
                pthread_create(&threads[0],NULL,OpenTask,NULL);
		sem_post(&lock);
                break;
            case 2:
                pthread_create(&threads[1],NULL,CopyFile,NULL);
		sem_post(&lock);
                break;
            case 3:
                pthread_create(&threads[2],NULL,CutFile,NULL);
		sem_post(&lock);
                break;
            case 4:
                pthread_create(&threads[3],NULL,CreateFolder,NULL);
		sem_post(&lock);
                break;
            case 5:
                pthread_create(&threads[4],NULL,ShowFiles,NULL);
		sem_post(&lock);
                break;
            case 6:
                pthread_create(&threads[5],NULL,DelFiles,NULL);
		sem_post(&lock);
                break;
            case 7:
                pthread_create(&threads[6],NULL,DelDir,NULL);
		sem_post(&lock);
                break;
            default:
		sem_destroy(&lock);
		return 0;
                break;
        }
    }
}
