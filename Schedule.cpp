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

vector<processo> processListRR, processListFCFS, processListPS;
int tempoProcessFCFS[10], tempoProcessRR[10], tempoProcessPS[10];//guarda tempo que cada processo foi processado

bool compareFCFS(processo a, processo b){
	return a.arrival <= b.arrival;
}

void Fcfs()//Firs Come First Service Nao Preemptivo
{
	cout<<"Arrival "<<"Time "<<"Priority "<<endl;
	
	sort (processListFCFS.begin(), processListFCFS.begin()+10, compareFCFS);
	
	for(int i=0;i<processListFCFS.size();i++)
    { 
        cout<<processListFCFS[i].arrival<<"      "<<processListFCFS[i].time<<"     "<<processListFCFS[i].priority<<" - Processo "<<i+1<<endl;
    } 
	
    for(int i=0;i<processListFCFS.size();i++)
    { 
    	cout<<"Etapa do processamento: "<<endl;
        for(int j=0; j<processListFCFS[i].time; j++){
        	cout<<"Etapa "<<j+1<<" de "<<processListFCFS[i].time<<endl;
        	tempoProcessFCFS[i]++;
		}
		if(tempoProcessFCFS[i] == processListFCFS[i].time){
			processListFCFS[i].finished = true;
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

void PsPreemp()//Priority Schedule Preemptivo
{
	cout<<"Arrival "<<"Time "<<"Priority "<<endl;
	int tempo = 0, prioridadeMaior = 6, posPrioridadeMaior = 0, processosTerminados = 0;
	sort (processListPS.begin(), processListPS.begin()+10, comparePS);
    for(int i=0;i<processListPS.size();i++)
    { 
        cout<<processListPS[i].arrival<<"      "<<processListPS[i].time<<"     "<<processListPS[i].priority<<" - Processo "<<i+1<<endl;
    }
	
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < processListPS.size(); j++){
			if(processListPS[j].arrival <= tempo && processListPS[j].priority < prioridadeMaior && processListPS[j].finished == false){
				prioridadeMaior = processListPS[j].priority;
				posPrioridadeMaior = j;
			}
		}
		if(tempoProcessPS[posPrioridadeMaior] != processListPS[posPrioridadeMaior].time){
        	cout<<"Etapa "<<tempoProcessPS[posPrioridadeMaior]+1<<" de "<<processListPS[posPrioridadeMaior].time<<" do processo "<< (posPrioridadeMaior)+1<<endl;
        	tempoProcessPS[posPrioridadeMaior]++;
		} 
        if(tempoProcessPS[posPrioridadeMaior] == processListPS[posPrioridadeMaior].time && processListRR[posPrioridadeMaior].finished == false && processosTerminados < 10 ){
			processListPS[posPrioridadeMaior].finished = true;
			cout<<"Processo "<<(posPrioridadeMaior)+1<<" terminou."<<endl;
			prioridadeMaior = 6;
			processosTerminados++;
		}
		tempo++;
	}     
}

void RR()//Round Robin
{
	cout<<"Arrival "<<"Time "<<"Priority "<<endl;
	int etapas = 0;//Numero total de etapas de todos os processos
	sort (processListRR.begin(), processListRR.begin()+10, compareFCFS);
	for(int i=0;i<processListRR.size();i++)
    { 
        cout<<processListRR[i].arrival<<"      "<<processListRR[i].time<<"     "<<processListRR[i].priority<<" - Processo "<<i+1<<endl;
        etapas += processListRR[i].time;
    } 
	
    for(int i=0; i < 100; i++)
    {
		if(tempoProcessRR[i%10] != processListRR[i%10].time){
        	cout<<"Etapa "<<tempoProcessRR[i%10]+1<<" de "<<processListRR[i%10].time<<" do processo "<< (i%10)+1 <<endl;
        	tempoProcessRR[i%10]++;
		} 
        if(tempoProcessRR[i%10] == processListRR[i%10].time && processListRR[i%10].finished == false){
			processListRR[i%10].finished = true;
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
    
    	processListFCFS.push_back(processAux);
    	processListRR.push_back(processAux);
    	processListPS.push_back(processAux);
	}
	
    
    cout<<endl<<endl<<endl<<"Algoritmo Priority Schedule Preemptivo"<<endl<<endl;
    PsPreemp();
    cout<<endl<<endl<<endl<<"Algoritmo FCFS"<<endl<<endl;
    Fcfs();
    cout<<endl<<endl<<endl<<"Algoritmo Round Robin"<<endl<<endl;
    RR();
    
	
      
    /*// creating thread objects
    pthread_t thrd_1;
    pthread_t thrd_2;
    pthread_t thrd_3;
    // create thread
    //pthread_create(&thrd_1,NULL,Fcfs,(void *)&a);
    pthread_create(&thrd_2,NULL,PsPreemp,(void *)0);   
    //pthread_create(&thrd_3,NULL,RR,(void *)0); 
	 
    //pthread_join(thrd_1, (void **)&status);
    //pthread_join(thrd_2, (void **)&status);
    pthread_join(thrd_3, (void **)&status);
    
    system("PAUSE");*/
    return 0;
}
