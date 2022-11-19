//Create a producer/consumer problem for the a "Raspberry PI" structure.
//
//    you should use 2 producers
//        Producer 1 creates a new "R_PI" at a random time in between 0s and 3 s
//        Producer 2 creates a new "R_PI" at a random time in between 0s and 5 s
//    a new consumer (student) is trying to get/buy a "R_PI" every 1s
//        each consumer will be in a sep thread
//
//    use a global list to hold each available "Raspberry PI"
//        each "R_PI" will have: ID, next(for list implementation) ....
//        you will have to use malloc for each new "R_PI"
//        max size for the list = 20

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
static pthread_cond_t full = PTHREAD_COND_INITIALIZER;
static int ready=0;
static int done =0; 
static int count = 0;
static int fullcount = 1;

typedef struct raspberry_pi{
    int id;
    struct raspberry_pi *pNext;
} R_pi;

R_pi *head = NULL;
void pop()
{
    R_pi *temp_head;
   // printf("\nRaspberry PI #: %d has successfully been popped!\n", head->id );
    temp_head = head; 
    head = head->pNext;
    free(temp_head);//
}

R_pi *create_new_r_pi()
{
    R_pi *result = (R_pi*)malloc(sizeof(R_pi));
    result->id = fullcount;
    result->pNext = NULL;
    return result;
}

static void* thread_producer1(void *args)
{
    int ret;
    for (;done<100;)
    {
        srand(time(NULL));
        //int r  = (rand()%(6)); //in this case the linked lists reaches its limit fast'
        int r  = (rand()%(5+1-1))+1; // In this case your linked list slowly builds...
        ret = pthread_mutex_lock(&mtx); //Lock as soon as you enter
        
        if (ret!=0) return NULL; //do all that needs to be done
        if (count == 20)
        {
            printf("\nStock is full\n");
            ret = pthread_cond_wait(&full,&mtx);
        }
        R_pi *new_r_pi = create_new_r_pi();
        if(head==NULL)
        {
            head = new_r_pi;  
        }
        else
        {
            new_r_pi->pNext=head; 
            head = new_r_pi;
        }
        count = count+1;
        fullcount = fullcount+1;
        printf ("Producer 1 (Rand 5 Seconds) has made a new R-Pi. Its ID is: %d\n",new_r_pi->id);
        printf ("Total R-Pis left = %d\n",count);
        pthread_cond_signal(&empty); //no longer empty
        ret = pthread_mutex_unlock(&mtx); //unlock the mutex
        if (ret!=0) return NULL;
        sleep(r); //every R second seconds
    }
}
static void* thread_producer2(void *args) //
{
    int ret;
    for (;done<100;)
    {
        srand(time(NULL));
        //int z = (rand()%4); // R  = %4 because rand()% (max+1-min) + min 
        int z = (rand()%(3+1-1))+1; // R  = %4 because rand()% (max+1-min) + min 
        ret = pthread_mutex_lock(&mtx); //Lock as soon as you enter
        if (ret!=0) return NULL; //do all that needs to be done
        if (count == 20)
        {
            printf("Stock is full\n");
            ret = pthread_cond_wait(&full,&mtx);
            if (ret!=0) return NULL;
        }
        
        R_pi *new_r_pi = create_new_r_pi();
        if(head==NULL)
        {
            head = new_r_pi;
        }
        else
        {
            new_r_pi->pNext=head;
            head = new_r_pi;
        }
        count = count+1;
        fullcount = fullcount +1;
        printf ("Producer 2 (Rand 3 Seconds) has made a new R-Pi. Its ID is: %d\n",new_r_pi->id);
        printf ("Total R-Pis left = %d\n",count);
        pthread_cond_signal(&empty);
        ret = pthread_mutex_unlock(&mtx); //unlock the mutex
        if (ret!=0) return NULL;
        sleep(z); //every Z Seconds
    }

}
static void* thread_consume(void *args)
{
    int ret;
    //for (;done<100;)
    //{
        ret = pthread_mutex_lock(&mtx); //lock as soon as it enters
        if (ret!=0) return NULL;
        while (head==NULL) //
        {
            printf("Waiting for stock...\n");
            ret = pthread_cond_wait(&empty,&mtx); //empty condition
            if (ret!=0) return NULL;
        }
        if (head!=NULL)
        {
            count = count-1;
            printf("The consumer thread (A student) has just purchased R-pi with ID#%d\n",head->id);
            printf("Total R-Pis left = %d\n",count);
            pop();
            pthread_cond_signal(&full);
            ++done;
        }
        ret = pthread_mutex_unlock(&mtx); //unlock after it is done.
        if (ret!=0) return NULL;
        sleep(1); 
    //}
}



int main(int argc, char* argv[])
{
    pthread_t t1,t2,t3;
    int loops,ret;
    //loops = (argc>1)?atoi(argv[1]):1000000;
    
    ret = pthread_create(&t1,NULL,thread_consume,NULL);
    ret = pthread_create(&t2,NULL,thread_producer1,NULL);
    ret = pthread_create(&t3,NULL,thread_producer2,NULL);
    while(1)
    {
        pthread_join(t1,NULL);
        ret = pthread_create(&t1,NULL,thread_consume,NULL);
        printf("\n==========================================\n\n");
    }
}

