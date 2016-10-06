#include <dirent.h>  //struct dirent, opendir, closedir, readdir를 불러온다. struct dirent안의 d_name이란 변수를 사용할 예정
#include <sys/stat.h>  //struct stat, lstat, S_ISDIR을 불러온다 struct stat st_mode을 사용할 예정 
#include <stdio.h>  
//#include <time.h>
#include <sys/time.h>  //시간을 재기위함. timeval과 gettimeofday를 불러와 사용할 예정

int is_what(const char* path){  //해당파일이 일반파일인지 디렉토리파일인지 알아보는 함수
	struct stat buf;  //<sys/stat.h>에서 가져온 구조체로 변수를 선언한다
	if(lstat(path, &buf)<0){  //해당경로의 파일의 정보를 버퍼에 옮긴다
		printf("lstat : Path does not exist.\n");
		return -1;  //이때 리턴값이 0보다 작으면 에러메세지 출력
	}
	if(S_ISREG(buf.st_mode))  //S_함수로 레귤러파일이면 0, 디렉토리파일이면 1을 리턴
		return 0;
	else if(S_ISDIR(buf.st_mode))
		return 1;
}
int listdir_a(const char* path){  //-a옵션일 때, 파일이름을 출력하는 함수
	struct dirent *entry;  //<dirent.h>에서 가져온 구조체로 변수를 선언
	DIR *dp;  //디렉토리 스트림 변수를 선언한다 (fp처럼 dp가 일반적으로 사용됨)
	char buff[1024];  //경로를 만들기 위한 버퍼변수

	dp = opendir(path);  //해당경로의 디렉토리를 오픈해서
	if(dp == NULL){
		printf("opendir : Path does not exist or could not be read.\n");
		return -1;
	}  //해당 경로의 파일이 디렉토리파일이 아니거나 존재하지 않으면 오류출력
	
	while((entry = readdir(dp))){  //구조체포인터에 해당 경로의 디렉토리파일정보를 할당
		sprintf(buff,"%s/%s",path,entry->d_name);  //경로 = 현재경로/파일이름
		if(is_what(buff) == 1)  //그경로가 폴더라면 디렉토리라면!
			printf("%c[1;34m%s\n%c[0m",27,entry->d_name,27);  //파란색으로 출력
		else puts(entry->d_name);  //일반 파일이면 그냥 출력
	}  //더이상 할당할 것이 없을 때까지 할당 받으면서 파일의 이름을 출력한다
	closedir(dp);  //디렉토리스트림을 닫는다
	return 0;
}
int listdir_non(const char* path){  //옵션이 없을 때 파일이름을 출력하는 함수
	struct dirent *entry;
	DIR *dp;
	char buff[1024];

	dp = opendir(path);
	if(dp == NULL){
		printf("opendir : Path does not exist or could not be read.\n");
		return -1;
	}

	while((entry = readdir(dp))){
		if(entry->d_name[0] != '.'){
			sprintf(buff,"%s/%s",path,entry->d_name);
			if(is_what(buff) == 1)
				printf("%c[1;34m%s\n%c[0m",27,entry->d_name,27);		
			else puts(entry->d_name);
		}
	}  //거의 -a옵션과 같지만 이부분에서 이름 맨앞이 .인(숨겨진) 파일들은 제외하고 출력
	closedir(dp);
	return 0;
}
int listdir_R(const char* path){  //-R옵션일 때 사용하는 함수
	struct dirent *entry;  
	DIR *dp;
	char buff[1024];  //파일경로와 파일이름을 합쳐 새로운 경로를 만들 변수

	printf("%s:\n",path);
	listdir_non(path);
	printf("\n");  //해당 경로의 파일들을 일단 출력

	dp = opendir(path);
	if(dp == NULL){
		printf("opendir : Path does not exist or could not be read.\n");
		return -1;
	}  //그리고 나서 해당경로의 디렉토리를 오픈

	while((entry = readdir(dp))){
		if(entry->d_name[0] != '.'){
			sprintf(buff,"%s/%s",path,entry->d_name);  //경로 = 해당경로/파일이름
			if(is_what(buff) == 1)	//새로운 경로가 디렉토리이면!
				listdir_R(buff);  //해당경로로 리퀄시브해준다
		}
	}
	closedir(dp);
	return 0;
}
int main(int argc, char* argv[]){  //메인함수
	//int i;
	//clock_t tmp1, tmp2;
	//double time;  //클락으로 시간을 재려다가 실패한 부분.
	//for(i=0;i<argc;i++)
		//printf("%s\n",argv[i]);  //이부분은 argc와 argv를 이해하기위해 작성한 코드
	//tmp1 = clock();
	struct timeval time_1;  //sys/time.h 에서 불러온 구조체로 변수선언
	struct timeval time_2;
	gettimeofday(&time_1, NULL);  //현재시간을 변수에 저장

	if(argc == 1)  //만약 옵션도 없고 파일경로도 없다면
		listdir_non(".");  //현재디렉토리로 논옵션함수를 부른다
	else if(argc == 2){  //옵션만 있거나 파일경로만 있다면
		if(strcmp(argv[1],"-a")==0)  //-a옵션이면
			listdir_a(".");  //현재디렉토리로 -a옵션함수를 부른다
		else if(strcmp(argv[1],"-R")==0)  //-R옵션이면
			listdir_R(".");  //현재디렉토리로 -R옵션함수를 부른다
		else listdir_non(argv[1]);  //파일경로만 있다면 해당경로로 논옵션함수 호출
	}
	else if(argc == 3){  //옵션과 경로를 함께준 경우
		if(strcmp(argv[1],"-a")==0)  //-a옵션이라면
			listdir_a(argv[2]);  //해당경로로 -a옵션함수를 호출
		else if(strcmp(argv[1],"-R")==0)  //-R옵션이라면
			listdir_R(argv[2]);  //-R옵션함수를 호출
	}
	//tmp2 = clock();
	//time = (double)(tmp2-tmp1)/CLOCKS_PER_SEC;
	//printf("time to execute : %.0fms\n",(double)time*1000000000);
	gettimeofday(&time_2, NULL);  //현재시간을 변수에 저장
	printf("time to execute : %dms\n",(int)(time_2.tv_usec-time_1.tv_usec));  //구조체 변수에 있는 마이크로세컨드의 단위로된 .tv_usec을 불러내서 빼준뒤 출력한다.
	return 0;
}	
