#include <stdio.h>

struct process{
	int id;
	int burst;
	int priority;
	int wait;
};  //프로세스 구조체 : 아이디, 버스트타임, 우선순위의 정보가 들어감.

int NUM = 0;  //프로세스 갯수 (전역변수).
struct process pro[5];  //최대 5개의 프로세스.
void init_pro();  //process의 모든 값을 0으로 세팅하는 초기화 함수.
void fcfs();
void sjf();
void priority();
void RR(int timer);

int main(int argc, char *argv[]){
	int i;	
	int total_burst=0;  //총 수행시간을 저장하는 변수.
	int timer;  //RR를 위해 받는 타이머 변수.
	int whatschedule;  //어떠한 스케쥴링을 할 것인지 받는 변수.
	FILE *fp;  //파일을 열고 닫기 위한 변수.

	init_pro();  //프로세스 초기화.
	fp = fopen(argv[1],"r");  //실행 뒤의 인자를 받아서 오픈한다.
	if(fp==NULL){
		printf("%s DOES NOT EXIST.\n",argv[1]);
		return 0;
	}  //만약에 파일이 없다면 메세지를 출력하고 프로그램을 종료.

	fscanf(fp,"%d",&NUM);  
	  //맨처음 값을 읽는다. (프로세스의 갯수).
	fgetc(fp);  //줄 띄움으로 인해 읽히는 값은 버린다.

	for(i=0;i<NUM;i++){
		fscanf(fp,"%d",&pro[i].id);
		fscanf(fp,"%d",&pro[i].burst);
		fscanf(fp,"%d",&pro[i].priority);  //각 프로세스의 정보를 읽어 저장.
		fgetc(fp);  //줄 띄움으로 인해 읽히는 값은 버림.
	}  //모든 프로세스의 정보를 읽어 저장.

	printf("\nPROCESS NUMBER : %d\n",NUM);
	for(i=0;i<NUM;i++){
		printf("P%d	%d	%d\n",pro[i].id,pro[i].burst,pro[i].priority);
	}  //인풋파일의 내용을 출력한다.

	printf("\nPLZ INPUT NUMBER FOR SCHEDULING(1:FCFS)(2:SJF)(3:PRIORITY)(4:RR)\n");
	scanf("%d",&whatschedule);  //스케쥴링을 결정하는 변수를 입력받는다.
	while(whatschedule>4||whatschedule<1){
		printf("from 1 to 4 PLZ ㅡㅡ.\n");
		scanf("%d",&whatschedule);
	}

	printf("\n");

	for(i=0;i<NUM;i++){
		total_burst += pro[i].burst;  //모든 수행시간을 더하면 총 수행시간.
	}

	if(whatschedule==4){
		printf("PLZ INPUT TIMER FOR RR\n");
		scanf("%d",&timer);
		while(timer<1){
			printf("ㅡㅡ.. positive num PLZ\n");
			scanf("%d",&timer);
		}  //TIMER값을 입력받는다.
	}
	
	printf("\nGANTT CHART : \n");
	printf("0");
	for(i=0;i<total_burst/5;i++){
		printf("        %d",(i+1)*5);  //8칸을 띈다.
	}printf("\n");  //차트 시간축 출력.

	if(whatschedule==1)  //FCFS
		fcfs();
	else if(whatschedule==2)  //SJF
		sjf();
	else if(whatschedule==3)  //PRIORITY
		priority();
	else if(whatschedule==4)  //ROUND ROBIN
		RR(timer);
	return 0;
}

void init_pro(){
	int i;
	for(i=0;i<5;i++){
		pro[i].id = 0;
		pro[i].burst = 0;
		pro[i].priority = 0;
		pro[i].wait = 0;
	}
}  //프로세스의 모든 값을 0으로 초기화해준다.

void fcfs(){
	int i,j;
	int total_wait = 0;
	int count = 0;
	for(i=0;i<NUM;i++){  //그냥 순서대로 실행한다.
		pro[i].wait = count;  //카운트의 값을 넣는다.
		for(j=0;j<pro[i].burst;j++){
			printf(" %d",pro[i].id);
			count++;  //프로세스가 실행되는 동안 카운트를 ++한다.
		}
	}
	//다른 프로세스가 먼저 실행되는 동안 카운트를 ++해서 자기가 실행되는 차례에 그 값을 넣어버린다. 그러면 기다린 동안의 시간이 들어가는 것과 같다.
	printf("\n\n");
	for(i=0;i<NUM;i++){
		printf("PROCESS %d WAITING TIME : %d SEC\n",pro[i].id,pro[i].wait); 
		total_wait += pro[i].wait;
	}  //웨이팅타임 출력.
	printf("AVERAGE WAITING TIME : %f SEC\n\n",(float)total_wait/NUM);
	//에버리지 타임 출력.
}

void sjf(){
	int i,j;
	int total_wait = 0;  
	int count = 0;
	int tmp1, tmp2, tmp3;  //소팅에서 자리를 바꾸기 위한 변수.
	for(i=1;i<NUM;i++){
		for(j=0;j<NUM-i;j++){
			if(pro[j].burst > pro[j+1].burst){  //버스트타임을 기준으로 버블소팅.
					//뒤에꺼가 나보다 작으면 바꾼다.
					//바꿀때 버스트와 아이디와 우선순위 다 바꿈.
				tmp1 = pro[j].burst;
				pro[j].burst = pro[j+1].burst;
				pro[j+1].burst = tmp1;
				tmp2 = pro[j].id;
				pro[j].id = pro[j+1].id;
				pro[j+1].id = tmp2;
				tmp3 = pro[j].priority;
				pro[j].priority = pro[j+1].priority;
				pro[j+1].priority = tmp3;  //버스트 기준으로 소팅.
			}
		}
	}
	for(i=0;i<NUM;i++){
		pro[i].wait = count;
		for(j=0;j<pro[i].burst;j++){
			printf(" %d",pro[i].id);
			count++;
		}
	} //fcfs에서와 같은 방법으로 웨이팅을 계산하면서 실행과정을 출력한다.
	printf("\n\n");
	for(i=0;i<NUM;i++){
		printf("PROCESS %d WAITING TIME : %d SEC\n",pro[i].id,pro[i].wait);
		total_wait += pro[i].wait;
	}
	printf("AVERAGE WAITING TIME : %f SEC\n\n",(float)total_wait/NUM);
}

void priority(){
	int i,j;
	int total_wait = 0;
	int count = 0;
	int tmp1, tmp2, tmp3;
	for(i=1;i<NUM;i++){
		for(j=0;j<NUM-i;j++){
			if(pro[j].priority > pro[j+1].priority){  //우선순위를 기준으로 버블소팅.
				tmp1 = pro[j].burst;
				pro[j].burst = pro[j+1].burst;
				pro[j+1].burst = tmp1;
				tmp2 = pro[j].id;
				pro[j].id = pro[j+1].id;
				pro[j+1].id = tmp2;
				tmp3 = pro[j].priority;
				pro[j].priority = pro[j+1].priority;
				pro[j+1].priority = tmp3;
			}
		}
	}  //sjf의 방법과 같이 소팅방법이 같다.
	for(i=0;i<NUM;i++){
		pro[i].wait = count;
		for(j=0;j<pro[i].burst;j++){
			printf(" %d",pro[i].id);
			count++;
		}
	}  //똑같이 웨이팅을 계산하고 실행과정을 출력한다.
	printf("\n\n");
	for(i=0;i<NUM;i++){
		printf("PROCESS %d WAITING TIME : %d SEC\n",pro[i].id,pro[i].wait);
		total_wait += pro[i].wait;
	}
	printf("AVERAGE WAITING TIME : %f SEC\n\n",(float)total_wait/NUM);
}

void RR(int timer){
	int i,j;
	int total_wait = 0;
	int remain[5] = {0,0,0,0,0};  //리메인배열. 프로세스의 남아있는 일의 버스트타임을 저장하는 배열이다.
	for(i=0;i<NUM;i++){
		remain[i] = pro[i].burst;
	}  //일단 리메인 값을 버스트타임으로 세팅한다.
	while(remain[0]!=0||remain[1]!=0||remain[2]!=0||remain[3]!=0||remain[4]!=0){
			//리메인값이 모두 0이 될때까지.
		for(i=0;i<NUM;i++){  //각 프로세스
			for(j=0;j<timer;j++){  //타이머만큼
				if(remain[i]==0) break;  //남은 일이 없으면 바로 브레이크.
				printf(" %d",pro[i].id);  //그렇지 않다면 실행.
				remain[i]--;  //실행후 리메인 값을 줄인다.
				if(remain[(i+1)%5]!=0) pro[(i+1)%5].wait++;
				if(remain[(i+2)%5]!=0) pro[(i+2)%5].wait++;
				if(remain[(i+3)%5]!=0) pro[(i+3)%5].wait++;
				if(remain[(i+4)%5]!=0) pro[(i+4)%5].wait++; 
					//다른 프로세스의 일이 남아있으면 웨이트타임을 ++
					//왜냐하면 일이 남아있어야 기다리고
					//일이 안남아 있으면 안기다려도 되니깐 ㅎ.ㅎ
			}
		}
	}
	printf("\n\n");
	for(i=0;i<NUM;i++){
		printf("PROCESS %d WAITING TIME : %d SEC\n",pro[i].id,pro[i].wait);
		total_wait += pro[i].wait;
	}  //그리고 웨이트타임 출력
	printf("AVERAGE WAITING TIME : %f SEC\n\n",(float)total_wait/NUM);
}
