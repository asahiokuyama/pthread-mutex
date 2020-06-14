#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int i;
//同期のために使うmutex
pthread_mutex_t mutex;

pthread_t tid[2];

void *f1(void *arg){
    for (int i = 0; i < 5; i++)
    {
        //lock
        pthread_mutex_lock(&mutex);
        printf("f1 out");
        //1u秒止めている
        usleep(1);
        printf("f1 call no.%d\n",i);
        //unlock
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *f2(void *arg){
    for (int i = 0; i < 5; i++)
    {
        //lock
        pthread_mutex_lock(&mutex);
        printf("f2 out");
        //1u秒止める
        usleep(1);
        printf("f2 call no.%d\n",i);
        //unlock
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    //pthread_mutex_t型の変数を使うための初期化
    pthread_mutex_init(&mutex,NULL);
    
    //スレッドの生成 pthread_create(pthread_t型変数、NULL、実行関数、その引数)
    pthread_create(&tid[0],NULL,f1,(void *)1);
    pthread_create(&tid[1],NULL,f2,(void *)1);
    

    for (int i = 0; i < 2; i++)
    {
        //スレッドの終了待ち pthread_join(終了を待つスレッド、終了値を返すポインタだがここはNULL)
        pthread_join(tid[i],NULL);
    }
    printf("all thread terminated\n");
    //不用になったmutex用の変数に使われていた領域の解放
    pthread_mutex_destroy(&mutex);
    return 0;
    
}