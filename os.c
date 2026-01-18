#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

int size;
int *num;
pid_t p[16];
sem_t lock;
int ram = 0;
int memReq[16];
int input;

void clearScreen() {
    system("clear");
}
void welcome() {
  clearScreen();
    printf("\033[1m\033[32m  W   W  \033[33m  EEEEE  \033[34m L       L     \n");
    usleep(150000); // introduce a 150 millisecond delay

    printf("\033[1m\033[32m  W   W  \033[33m  E       \033[34m L       L     \n");
    usleep(150000);

    printf("\033[1m\033[32m  W W W  \033[33m  EEEEE   \033[34m L       L     \n");
    usleep(150000);

    printf("\033[1m\033[32m  WW WW  \033[33m  E       \033[34m L       L     \n");
    usleep(150000);

    printf("\033[1m\033[32m   W W   \033[33m  EEEEE  \033[34m LLLLLL  LLLLLL  \n");
    usleep(150000);

    printf("\033[1m\033[32m  CCCCC  \033[33m  OOOOO  \033[34m M     M  \033[35m EEEEE     \n");
    usleep(150000); // introduce a 150 millisecond delay

    printf("\033[1m\033[32m C       \033[33m O     O \033[34m MM   MM  \033[35m E         \n");
    usleep(150000);

    printf("\033[1m\033[32m C       \033[33m O     O \033[34m M M M M  \033[35m EEEEE     \n");
    usleep(150000);

    printf("\033[1m\033[32m C       \033[33m O     O \033[34m M  M  M  \033[35m E         \n");
    usleep(150000);

    printf("\033[1m\033[32m  CCCCC  \033[33m  OOOOO  \033[34m M     M  \033[35m EEEEE     \n");
    usleep(150000);
}

struct process {
    int p1;
};
struct ReadyQueue {
    struct process queue[10];
    int front;
    int rear;
};
struct ReadyQueue RQ = { .front = -1, .rear = -1 };
int isFull(struct ReadyQueue* q) {
    return (q->rear + 1) % 10 == q->front;
}
int isEmpty(struct ReadyQueue* q) {
    return q->front == -1 && q->rear == -1;
}
void enqueue(struct ReadyQueue* q, int pro) {
    if (isFull(q)) {
        printf("Error: Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    else {
        q->rear = (q->rear + 1) % 10;
    }
    q->queue[q->rear].p1 = pro;
}

int dequeue(struct ReadyQueue* q) {
    if (isEmpty(q)) {
        return -1;
    }
    int pid = q->queue[q->front].p1;
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else {
        q->front = (q->front + 1) % 10;
    }
    return pid;
}

void AssResources() {
    printf("the number of cores is : %d \n", num[0]);
    printf("the storage of hard drive is : %d GB.\n", num[1]);
    printf("the size of RAM is : %d GB.\n", num[2] );
    
    ram = num[2] * 1024;
  }

void Boot_loader() {
    clearScreen();
    char  pass[50] = { 0 }, temP[50] = { 0 };
    int flag = 1;
    printf("Welcome to mini OS\n");
    printf("Aneela ---- Eman\n");
    strcpy(pass, "1122");
    printf("Assigning Resources\n");
    AssResources();
    while (flag) {
        printf("Enter Login information:\n");
        printf("Enter password: ");
        scanf("%s", temP);
        if ((strcmp(temP, pass) == 0)) {
            printf("Login Successful\n");
            flag = 0;
        }
        else {
            printf("Incorrect Information\n");
        }
    }
}

void* runCalculator(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
      p[0] = fork();
        if (p[0] == 0) {          
            if(input == 1){
              char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./calculator.sh", NULL };
               if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
            }
            else if (input==0){
              char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./calculator", NULL };
               if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
            }
            else{
               printf("invalid input");
            }
           
        }
        else {
            int status;
            waitpid(p[0], &status, 0);
            ram += memReq[0];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[0] = 20;
        enqueue(&RQ, 0);
    }
    pthread_exit(NULL);
}

void* runClock(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[1] = fork();
        if (p[1] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./clock.sh", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[1], &status, 0);
            ram += memReq[1];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[1] = 15;
        enqueue(&RQ, 1);
    }
    pthread_exit(NULL);
}

void* runVLC(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[2] = fork();
        if (p[2] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./vlc.sh", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[2], &status, 0);
            ram += memReq[2];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[2] = 100;
        enqueue(&RQ, 2);
    }
    pthread_exit(NULL);
}

void* runfp(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[3] = fork();
        if (p[3] == 0) {
          system("gnome-terminal -- /bin/bash -c './filep; exec bash'");
        }
        else {
            int status;
            waitpid(p[3], &status, 0);
            ram += memReq[3];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[3] = 50;
        enqueue(&RQ, 3);
    }
    pthread_exit(NULL);
}

void* runFileExplorer(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[5] = fork();
        if (p[5] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./fileExp", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[5], &status, 0);
            ram += memReq[5];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[5] = 100;
        enqueue(&RQ, 5);
    }
    pthread_exit(NULL);
}

void* runBrowser(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[4] = fork();
        if (p[4] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./browser.sh", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[4], &status, 0);
            ram += memReq[4];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[4] = 200;
        enqueue(&RQ, 4);
    }
    pthread_exit(NULL);
}

void* runCal(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[6] = fork();
        if (p[6] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./calen.sh", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[6], &status, 0);
            ram += memReq[6];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[6] = 10;
        enqueue(&RQ, 6);
    }
    pthread_exit(NULL);
}

void* runTM(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[7] = fork();
        if (p[7] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./taskM.sh", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[7], &status, 0);
            ram += memReq[7];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[7] = 50;
        enqueue(&RQ, 7);
    }
    pthread_exit(NULL);
}

void* runNote(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[8] = fork();
        if (p[8] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./texteditor", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[8], &status, 0);
            ram += memReq[8];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[8] = 60;
        enqueue(&RQ, 8);
    }
    pthread_exit(NULL);
}

void* runGames(void* arg) {
    int arg_value = *((int*)arg);
    sem_wait(&lock);
    if (arg_value) {
        p[9] = fork();
        if (p[9] == 0) {
            char* argv[] = { "gnome-terminal", "--disable-factory", "--", "./games", NULL };
            if (execvp(argv[0], argv) == -1) {
                perror("Error in execvp");
            }
        }
        else {
            int status;
            waitpid(p[9], &status, 0);
            ram += memReq[9];
            pthread_exit(NULL);
        }
    }
    else {
        memReq[9] = 300;
        enqueue(&RQ, 9);
    }
    pthread_exit(NULL);
}

void* terminateAll(void* arg) {
    sem_wait(&lock);
    int status;
    for (int i = 0; i < 7; i++) {
        pid_t pid = getpid();
        if (pid != p[i] && kill(p[i], SIGKILL) == -1) {
            perror("Error in kill");
        }
        else if (pid != p[i]) {
            waitpid(p[i], &status, WNOHANG);
        }
    }
    pthread_exit(NULL);
}


void* QueueHandeler(void* arg) {
    while (1) {
        int n = dequeue(&RQ), m = 1, o = 0;
        pthread_t threads[16];
        switch (n) {
        case 0:
            if (ram >= memReq[0]) {
                ram -= memReq[0];
                pthread_create(&threads[0], NULL, runCalculator, &m);
            }
            else {
                pthread_create(&threads[0], NULL, runCalculator, &o);
            }
            sem_post(&lock);
            break;
        case 1:
            if (ram >= memReq[1]) {
                ram -= memReq[1];
                pthread_create(&threads[1], NULL, runClock, &m);
            }
            else {
                pthread_create(&threads[1], NULL, runClock, &o);
            }
            sem_post(&lock);
            break;
        case 2:
            if (ram >= memReq[2]) {
                ram -= memReq[2];
                pthread_create(&threads[2], NULL, runVLC, &m);
            }
            else {
                pthread_create(&threads[2], NULL, runVLC, &o);
            }
            sem_post(&lock);
            break;
        case 3:
            if (ram >= memReq[3]) {
                ram -= memReq[3];
                pthread_create(&threads[3], NULL, runfp, &m);
            }
            else {
                pthread_create(&threads[3], NULL, runfp, &o);
            }
            sem_post(&lock);
            break;
        case 4:
            if (ram >= memReq[4]) {
                ram -= memReq[4];
                pthread_create(&threads[4], NULL, runBrowser, &m);
            }
            else {
                pthread_create(&threads[4], NULL, runBrowser, &o);
            }
            sem_post(&lock);
            break;
        case 5:
            if (ram >= memReq[5]) {
                ram -= memReq[5];
                pthread_create(&threads[5], NULL, runFileExplorer, &m);
            }
            else {
                pthread_create(&threads[5], NULL, runFileExplorer, &o);
            }
            sem_post(&lock);
            break;
        case 6:
            if (ram >= memReq[6]) {
                ram -= memReq[6];
                pthread_create(&threads[6], NULL, runCal, &m);
            }
            else {
                pthread_create(&threads[6], NULL, runCal, &o);
            }
            sem_post(&lock);
            break;
        case 7:
            if (ram >= memReq[7]) {
                ram -= memReq[7];
                pthread_create(&threads[7], NULL, runTM, &m);
            }
            else {
                pthread_create(&threads[7], NULL, runTM, &o);
            }
            sem_post(&lock);
            break;
        case 8:
            if (ram >= memReq[8]) {
                ram -= memReq[8];
                pthread_create(&threads[8], NULL, runNote, &m);
            }
            else {
                pthread_create(&threads[8], NULL, runNote, &o);
            }
            sem_post(&lock);
            break;
        case 9:
            if (ram >= memReq[9]) {
                ram -= memReq[9];
                pthread_create(&threads[9], NULL, runGames, &m);
            }
            else {
                pthread_create(&threads[9], NULL, runGames, &o);
            }
            sem_post(&lock);
            break;
        default:
            break;
        }
        sleep(0.5);
    }
    pthread_exit(NULL);
}


void menu() {
    int select = 0, m = 0;
    pthread_t threads[16];
    pthread_create(&threads[11], NULL, QueueHandeler, NULL);
    while (1) {
        clearScreen();
        printf("Ram Available is: %d\n", ram);
        printf("1)  Calculator\n");
        printf("2)  Clock\n");
        printf("3)  Media Player\n");
        printf("4)  File_info\n");
        printf("5)  Browser\n");
        printf("6)  File Explorer\n");
        printf("7)  Calender\n");
        printf("8)  Task Manager\n");
        printf("9)  Text Editor\n");
        printf("10) Games\n");
	printf("11) Refresh\n");
        printf("Press any other key to Shut Down system.\n");
        printf("Enter your selection: ");
        scanf("%d", &select);
        switch (select) {
        case 1:
            printf("enter 1 for GUI calculator and 0 for simple calculator : ");
            scanf("%d" , &input);
           pthread_create(&threads[0], NULL, runCalculator, &m);
            sem_post(&lock);
            break;
        case 2:
            pthread_create(&threads[1], NULL, runClock, &m);
            sem_post(&lock);
            break;
        case 3:
           pthread_create(&threads[2], NULL, runVLC, &m);
            sem_post(&lock);
            break;
        case 4:
           pthread_create(&threads[3], NULL, runfp, &m);
            sem_post(&lock);
            break;
        case 5:
           pthread_create(&threads[4], NULL, runBrowser, &m);
            sem_post(&lock);
            break;
        case 6:
          pthread_create(&threads[5], NULL, runFileExplorer, &m);
            sem_post(&lock);
            break;
        case 7:
           pthread_create(&threads[6], NULL, runCal, &m);
            sem_post(&lock);
            break;
        case 8:
            pthread_create(&threads[7], NULL, runTM, &m);
            sem_post(&lock);
            break;
        case 9:
            pthread_create(&threads[8], NULL, runNote, &m);
            sem_post(&lock);
            break;
        case 10:
          pthread_create(&threads[9], NULL, runGames, &m);
            sem_post(&lock);
            break;
	case 11:
	    break;
        default:
            clearScreen();
            printf("Signing out\n");
            printf("Shutting down\n");
            pthread_create(&threads[6], NULL, terminateAll, NULL);
            pthread_join(threads[6], NULL);
            sem_post(&lock);
            return;
            break;
        }
    }

}
int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("please enter at least 3 numbers in command\n");
        return 1;
    }
    
    size = argc - 1;
    num = (int *)malloc(size * sizeof(int));
    if (num == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < size; i++) {
        num[i] = atoi(argv[i + 1]);
    }
  
    sem_init(&lock, 0, 1);
    welcome();
    usleep(650000);
    Boot_loader(); 
    menu();   
    sem_destroy(&lock);
    free(num); // Free allocated memory
    return 0;
}
