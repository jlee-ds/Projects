#include <stdio.h>
#include <pthread.h>  //스레드와 뮤텍스를 사용하기 위해서 사용
#include <stdlib.h>  //랜덤변수를 발생시키기 위해서 사용
#include <sys/time.h>  //time(), usleep(), struct timeval, gettimeofday등을 사용

#define PN 4 //철학자의 수를 나타내는 변수.

enum{THINKING, HUNGRY, EATING} state[PN];  //상태는 배고픔,생각,먹기 3가지 존재.
int wait_flag[PN] = {0,};  //현재 자기가 밥 먹기를 기다리면 1, 아니면 0.
pthread_t philosophers[PN];  //철학자 스레드 
pthread_mutex_t test_mutex = PTHREAD_MUTEX_INITIALIZER;  //뮤텍스 테스트함수에 사용.
int eat_cnt[PN] = {0,};  //먹은 횟수.
float hungry_wait[PN] = {0,};  //배고픔 상태에서 기다린 시간.
int program_flag;  //프로그램_플래그 : 600초가 지나면 0이 되고 프로그램이 중단.

void test(int i);

void pickup(int i){  //배고플 때 젓가락을 들려하는 함수.
	state[i] = HUNGRY;  //배고픔.
		pthread_mutex_lock(&test_mutex);  //락
	test(i);  //내가 젓가락을 들고 밥을 먹을 수 있나?
		pthread_mutex_unlock(&test_mutex);  //언락
	if(state[i]!=EATING){  //못먹어
		wait_flag[i] = 1;  //기다린다.
		while(wait_flag[i]);  //기다린다.
	}
}

void putdown(int i){  //다 먹고 젓가락을 내려놓을 때 쓰는 함수.
	state[i] = THINKING;  //다먹었으니 생각하자.
		pthread_mutex_lock(&test_mutex);
	test((i+PN-1)%PN);  //내 왼쪽 놈 먹을 수 있나?
		pthread_mutex_unlock(&test_mutex);
		pthread_mutex_lock(&test_mutex);
	test((i+1)%PN);  //내 오른쪽 놈 먹을 수 있나?
		pthread_mutex_unlock(&test_mutex);
}

void test(int i){  //먹을 수 있는지 없는 지 검사하는 함수.
	if((state[(i+PN-1)%PN]!=EATING)&&(state[i]==HUNGRY)&&(state[(i+1)%PN]!=EATING)){
			//만약에 자신의 왼쪽 오른쪽이 모두 먹고있지 않고 자기가 배고프다면
		state[i] = EATING;  //먹어라!
		wait_flag[i] = 0;  //기다리지 말고 먹어라!
	}
}

void init(){  //모든 철학자의 상태를 생각하기로 초기화하는 함수
	int i;
	for(i=0;i<PN;i++) state[i] = THINKING;
}

void thinking(){  //생각하는 중..
	int rand_NUM;  //몇 msec를 기다릴지 저장하는 변수.
	rand_NUM = rand()%491 + 10;  //10~500 사이의 난수를 발생.
	printf("think : %d\n",rand_NUM);
	usleep(rand_NUM*1000);  
		//usleep의 단위는 마이크로초이기에 밀리초로 바꾸기위해 *1000을 한다
}

void eating(int i){  //먹자!
	eat_cnt[i]++;  //먹었으니 횟수를 증가시킨다.
	int rand_NUM;	
	rand_NUM = rand()%491 + 10;  //10~500 사이의 난수를 발생.
	printf("eat : %d\n",rand_NUM);
	usleep(rand_NUM*1000);  
		//usleep의 단위는 마이크로초이기에 밀리초로 바꾸기 위해 *1000을 한다.
}


void* Philosopher_do(void* id){  //철학자가 하는 일의 전부.
	int i = (int)id;  //철학자 넘버를 받아옴.
	struct timeval wait_s,wait_e;  //웨이트타임을 재기위한 변수.
	while(program_flag){  //프로그램이 실행중이면
		thinking();  //생각한다.
		if(program_flag==0) break;  
			//프로그램이 끝났으면 브레이크하는 부분.
		gettimeofday(&wait_s,NULL);  //시작
		pickup(i);  				//젓가락을 든다.
		gettimeofday(&wait_e,NULL);  //땡
		hungry_wait[i] += (float)((wait_e.tv_sec-wait_s.tv_sec)*1000000 + (wait_e.tv_usec-wait_s.tv_usec))/1000000;
			//얼마나 걸렸는 지 초단위로 계산한다. tv_sec은 초단위고 tv_usec은 마이크로 초 단위이므로 위와 같은 방법으로 초단위를 구한다.
		if(program_flag==0) break;
		eating(i);   			//먹자.
		if(program_flag==0) break;
		putdown(i);				//다 먹었으면 젓가락을 내려놓자.
	}
}

int main(int argc, char *argv[]){
	int i;
	float min_wait, max_wait, avg_wait, var_wait, total_w=0, tmp_w=0;  
		//웨이트타임 최소,최대,평균,분산 변수. 총합, 제곱의 총합.
	int min_eat, max_eat, total_e=0, tmp_e=0;  //먹은 거 최소, 최대. 총합. 제곱의 총합.
	float avg_eat, var_eat;  //먹은 거 평균, 분산.
	struct timeval pro_start, pro_end;  //프로그램 시간을 재는 변수.
	float _time = 0;  //총시간.

	srand(time(NULL));  //난수발생 시드제공.

	program_flag = 1;  //프로그램시작!
	for(i=0;i<PN;i++){
		pthread_create(&philosophers[i], NULL, Philosopher_do, (void*)i);
	}  			//철학자스레드를 만든다. 철학자가 하는일의 모든 것을 시작한다.

	gettimeofday(&pro_start,NULL);  //프로그램 시작시간

	while(_time<600){
		gettimeofday(&pro_end,NULL);
		_time = (float)(pro_end.tv_sec-pro_start.tv_sec);
		_time = _time + (float)(pro_end.tv_usec-pro_start.tv_usec)/1000000;
	}  //600초가 넘으면 와일문을 나오고
	program_flag = 0;  //프로그램이 종료됬다고 플래그를 0으로 바꾼다.

	for(i=0;i<PN;i++){
		printf("PHILOSOPHER %d EATING COUNT : %d.\n",i+1,eat_cnt[i]);
		printf("PHILOSOPHER %d WAIT TIME ON HUNGRY : %.3f SEC\n\n",i+1,hungry_wait[i]);	
	}  //각 철학자의 먹은 횟수와 배고픔시간을 출력한다.

	min_wait = max_wait = hungry_wait[0];  //최대와 최소를 초기화.
	min_eat = max_eat = eat_cnt[0]; 		//최대와 최소를 초기화.
	for(i=0;i<PN;i++){
		if(min_wait > hungry_wait[i]) min_wait = hungry_wait[i];
		if(max_wait < hungry_wait[i]) max_wait = hungry_wait[i];
		if(min_eat > eat_cnt[i]) min_eat = eat_cnt[i];
		if(max_eat < eat_cnt[i]) max_eat = eat_cnt[i]; 
	   		//리니어하게 조사하며 최대와 최소를 각각 구해낸다.
		total_w += hungry_wait[i];    //기다린 시간의 총합.
		tmp_w += hungry_wait[i] * hungry_wait[i];  //기다린 시간의 제곱의 총합.
		total_e += eat_cnt[i];		//먹은 횟수의 총합.
		tmp_e += eat_cnt[i] * eat_cnt[i];		//먹은 횟수의 제곱으 총합.
	}

	avg_wait = total_w / PN;  	//평균 = 총합/철학자수
	tmp_w = tmp_w / PN;			//제곱의 평균 = 제곱의 총합/철학자수
	var_wait = tmp_w - avg_wait * avg_wait;		//분산 = 제곱의 평균 - 평균의 제곱.
	avg_eat = (float)total_e / PN;
	tmp_e = tmp_e / PN;
	var_eat = (float) tmp_e - avg_eat * avg_eat; 
			//위와 같으나 카운트된 값은 인트형임으로 플로트형으로 바꿔준다.

	printf("MIN COUNT : %d\nMAX COUNT : %d\nAVG COUNT : %.3f\nCOUNT VARIANCE : %.3f\n\n",min_eat,max_eat,avg_eat,var_eat);
	printf("MIN WAIT TIME (%.3f SEC) in HUNGRY state\nMAX WAIT TIME (%.3f SEC) in HUNGRY state\n",min_wait,max_wait);
	printf("AVG WAIT TIME (%.3f SEC) in HUNGRY state\nVARIANCE WAIT TIME (%.6f SEC) in HUNGRY state\n\n",avg_wait,var_wait);
				//간단하게 출력한다.

	gettimeofday(&pro_end,NULL);
	_time = (float)(pro_end.tv_sec-pro_start.tv_sec);  //초단위
	_time = _time + (float)(pro_end.tv_usec-pro_start.tv_usec)/1000000;  
					//마이크로초단위임으로 10^6으로 나눠준다. 그것을 다 더한다.
	printf("TOTAL RUN TIME : %.3f SEC\n",_time);
		
	return 0;
}
