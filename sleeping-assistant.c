#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <semaphore.h>
#include <unistd.h>
#include <time.h> 

pthread_mutex_t mutex; /*Declaring a global mutex variable, only one can access it at a given point on time*/ 
int SIZE = 3;
sem_t sem;
int waitQueue[3] = {0, 0, 0}; /*Queue of size 3, because  we have 3 chair available for waiting*/
int front = -1, rear = -1; 
/*
*This solution is implemented using Circular Queue
*/
int isFull(){
    /*Function to check the waitQueue is Full or not */
    /*If it is full then return 1, else 0*/
    if( (front == rear + 1) || (front == 0 && rear == SIZE-1)) return 1;
    return 0;
}

int isEmpty(){
    /*Function to check the waitQueue is Empty or not */
    /*If it is empty then return 1, else 0*/
    if(front == -1) 
        return 1;
    return 0;
}

void display(){
    /*Fuction displays the current values present in the waitQueue*/
    int i;
    if(isEmpty()) 
        printf(" \n Empty Queue\n");
    else{
        printf("\n\n------ Wait queue current status : [ ");
        for( i = front; i!=rear; i = (i+1) % SIZE) {
            printf("%d ",waitQueue[i]);
        }
        printf("%d ",waitQueue[i]);
        
        printf("]-------\n\n");
    }
}
void enQueue(int element){
    /*Function to keep a Student in the wait queue*/
    if(isFull()) 
        printf("\n Queue is full!!, COME AFTER SOMETIME \n");
        
    else{
        printf("Wait for sometime in the queue\n");
        if(front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        waitQueue[rear] = element;
    }
}
int deQueue(){
    /*Function to remove a Student from the waitQueue if any*/
    int element;
    if(isEmpty()) {
        printf("\n Nobody to delete !! \n");
        return(-1);
    } 
    else {
        element = waitQueue[front];
        if (front == rear){
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % SIZE;
            
        }
        return(element);
    }
}
void *help(void *i){ /*It is the thread responsible for doubt solving of students*/
    /*
    *@param 1 : Unique id of Student
    */
    
    /* 
    *Fuction pthread_mutex_trylock(&mutex) return 0 if mutex lock availble on the variable 'mutex', 
    *else return error integer value.
    *@param 1 : mutex valriable
    */
    int lockStatus = pthread_mutex_trylock(&mutex); 
    
    int id =  *(int *)i; // Converting @param 1 to integer id.
    
    if( lockStatus == 0){ /*Program accuired mutex lock*/
    
        srand(time(NULL));
        /*-----------CRITICAL SECTION--------*/
        
        printf("Assistant is solving the doubt of student = %d \n", id);
        int randomTime = rand() % 10 + 5; /*Generating random time for sleep 5 to 15 seconds*/
        printf("Solving time = %d second(s)\n", randomTime);
        
        /*Thread will go for sleep for some time, this represents the doubt of Student is solving by teacher*/
        sleep(randomTime);
        
        printf("Doubt solved of Student = %d\n", id);
        
        while( !isEmpty() ){
        /*
        * Picking students waiting from the waitQueue and send them to the assistant for doubt solving
        */
            
            /* Solving doubt of students in queue */
            display(); //Displaying the student waiting in the queue
            id = deQueue();
            printf("Assistant is solving the doubt of student = %d \n", id);
            display();
            int randomTime = rand() % 10 + 5;/*Generating random time for sleep 5 to 15 seconds*/
            printf("Solving time = %d second(s)\n", randomTime);
            sleep(randomTime);
            /*Thread will go for sleep for some time, this represents the doubt of Student is solving by teacher*/
            printf("Doubt solved of Student = %d\n", id);
            
        }
        
        printf("\nNo more student in the queue, Assistant gone for sleep\nExiting the thread\n");
        pthread_mutex_unlock(&mutex); /*No more students in the queue, Mutex lock released*/
        pthread_exit(0);  /*Exiting thread*/
    }
    
    else{ /*Cannot enter Critical Section as some student is with teacher solving the doubt*/
        
        printf("Someone is with the assistant\n");
        /*Putting the student in the waitQueue*/
        enQueue(id);
        display();
        pthread_exit(0);
        
    }
    
}
int main(){

    pthread_mutex_init(&mutex, NULL); /*Initializing mutex variable with NULL*/
    sem_init(&sem, 0, 1);/*Initializing semaphore variable with 1*/
    pthread_t tid1;/*Creating the thread reference*/
    pthread_attr_t attr; /*Assigning default attributes*/
    pthread_attr_init(&attr);
    
    while(1){
        printf("\n\n\n-----------------------\n");
        printf("\t1. Doubt\n");
        printf("\t2. Exit\n");
        printf("-----------------------\n\n\n");
        printf("Enter your choice : \n");
        int choice;
        scanf("%d", &choice);
        
        switch(choice){
        
            case 1 :
                    sem_wait(&sem);
                        printf("Enter student id: ");
                        int i;
                        scanf("%d",&i);
                        int *id;
                        id = &i;
                        pthread_create(&tid1, &attr, help, id); /*Creating a thread process*/
                    sem_post(&sem);
                    break;
            case 2 : 
                    printf("Exiting program\n");
                    exit(0);
               
            default : printf("Invalid command\n");   
            
        }
        
    }

    pthread_join(tid1, NULL); /*Waiting for thread to complete*/
    
    return 0;
}
