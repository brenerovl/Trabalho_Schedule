#include <iostream>
#include <pthread.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct processo{
	int priority;
	int time;
	int arrival;
	bool finished;
};

vector<processo> processList;
int tempoProcess[10], tempoProcessRR[10];//guarda tempo que cada processo foi processado

bool compareFCFS(processo a, processo b){
	return a.arrival <= b.arrival;
}

void * Fcfs(void *data)//Firs Come First Service Nao Preemptivo
{
	int value = *((int *)data);
	sort (processList.begin(), processList.begin()+10, compareFCFS);
	
	for(int i=0;i<processList.size();i++)
    { 
        cout<<processList[i].arrival<<"      "<<processList[i].time<<"     "<<processList[i].priority<<" - Processo "<<i+1<<endl;
    } 
	
    for(int i=0;i<processList.size();i++)
    { 
    	cout<<"Etapa do processamento: "<<endl;
        for(int j=0; j<processList[i].time; j++){
        	cout<<"Etapa "<<j+1<<" de "<<processList[i].time<<endl;
        	tempoProcess[i]++;
		}
		if(tempoProcess[i] == processList[i].time){
			processList[i].finished = true;
			cout<<"Processo "<<i+1<<" terminou."<<endl;
		}
		
    }     
}

bool comparePS(processo a, processo b){
	if(a.arrival < b.arrival)return 1;
	else if(a.arrival > b.arrival)return 0;
	else if(a.priority <= b.priority)return 1;
	else if(a.priority > b.priority)return 0;
}

void * PsPreemp(void *data)//Priority Schedule Preemptivo
{
	sort (processList.begin(), processList.begin()+10, comparePS);
    for(int i=0;i<processList.size();i++)
    { 
        //cout<<processList[i].arrival<<"      "<<processList[i].time<<"     "<<processList[i].priority<<endl;
    }     
}

void * RR(void *data)//Round Robin
{
	int etapas = 0;//Numero total de etapas de todos os processos
	sort (processList.begin(), processList.begin()+10, compareFCFS);
	for(int i=0;i<processList.size();i++)
    { 
        cout<<processList[i].arrival<<"      "<<processList[i].time<<"     "<<processList[i].priority<<" - Processo "<<i+1<<endl;
        etapas += processList[i].time;
    } 
	
    for(int i=0; i < 100; i++)
    {
		if(tempoProcessRR[i%10] != processList[i%10].time){
        	cout<<"Etapa "<<tempoProcessRR[i%10]+1<<" de "<<processList[i%10].time<<" do processo "<< (i%10)+1 <<endl;
        	tempoProcessRR[i%10]++;
		} 
        if(tempoProcessRR[i%10] == processList[i%10].time && processList[i%10].finished == false){
			processList[i%10].finished = true;
			cout<<"Processo "<<(i%10)+1<<" terminou."<<endl;
		}
		
		
    }     
}

int numeroAleatorio(int menor, int maior) {
	
    return rand()%(maior-menor+1) + menor;
}



int main(int argc, char *argv[])
{
    int status, a = 10;
    processo processAux;
    
    srand((unsigned)time(0));
    for(int i = 0; i < 10; i++){
    	processAux.arrival = numeroAleatorio(0, 9);
    	processAux.priority = numeroAleatorio(1, 5);
    	processAux.time = numeroAleatorio(1, 10);
    	processAux.finished = false;
    
    	processList.push_back(processAux);
	}
	
    
    
    cout<<"Arrival "<<"Time "<<"Priority "<<endl;
    
	
      
    // creating thread objects
    pthread_t thrd_1;
    pthread_t thrd_2;
    pthread_t thrd_3;
    // create thread
    //pthread_create(&thrd_1,NULL,Fcfs,(void *)&a);
    //pthread_create(&thrd_2,NULL,PsPreemp,(void *)0);   
    pthread_create(&thrd_3,NULL,RR,(void *)0); 
	 
    //pthread_join(thrd_1, (void **)&status);
    //pthread_join(thrd_2, (void **)&status);
    pthread_join(thrd_3, (void **)&status);
    
    system("PAUSE");
    return 0;
}
