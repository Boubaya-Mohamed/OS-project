#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
#define WHT   "\x1B[37m"
int randomvalue(int min, int max) ;
int fileCreate(int PID) ;
int childWrite(int childFile ,int random,int fatherPIDRead ) ;
int childWrite1(int childFile ,int depacement,int fatherPIDRead ) ;
//==================

int fileCreate(int PID) {
char name[20] ;
char buf[4096] ;
sprintf(name,"PID%d.txt" ,PID) ;
return open(name ,O_CREAT | O_RDWR |O_APPEND) 
;
}
//==================
int childWrite(int childFile ,int random,int fatherPIDRead ){
char buf[4094] ;

if (childFile ==-1 && fatherPIDRead==0 ) {
  write(2,"Can't open PID200.txt \n" ,25)  ;
  return -1  ;
}
snprintf(buf,sizeof (buf),"son [%d] send [%d]\n",fatherPIDRead,random);
if(write(childFile, buf, strlen(buf))==-1)
{
return -1 ;
}
close(childFile) ;
return random ;

}
int childWrite1(int childFile ,int depacement,int fatherPIDRead ){
char buf[4094] ;
if (childFile ==-1 && fatherPIDRead==0 ) {
  write(2,"Can't open PID200.txt \n" ,25)  ;
  return -1  ;
}
snprintf(buf,sizeof (buf),"=============son [ %d ] is Dead with depacement [%d]\n",fatherPIDRead,depacement);
if(write(childFile, buf, strlen(buf))==-1)
{
return -1 ;
}
close(childFile) ;
return depacement ;

}
//==================
int randomvalue(int min, int max)
{
    int range, result, cutoff;
    if (min >= max)
        return min;
    range = max-min+1;
    cutoff = (RAND_MAX / range) * range;
    do {
 srand(getpid());
        result = rand();
    } while (result >= cutoff);
    return result % range + min;
}
int main(int ac , char * av[])
{

  int numChild  ;
  
   printf("How child would you creat ");
   scanf("%d", &numChild);
   char buf[90961],buf2[409400];

int dead ,sommedepacement=0,status,random,k, rapport ;
  int fatherPIDRead[2*numChild+1],PID[2*numChild+1] ;
  int RandomPIP[2*numChild] ,fatherRandomRead[2*numChild],SommeRandom[numChild+1] ,second[numChild+1];
  float moyendepacement=0 ;
   int  depacement [numChild+1] ;
   int deadPID[numChild+1] ;

system("clear");
for ( int i = 1; i <= numChild; i++ ) {
  pipe(&PID[2*i]);
  depacement[i] = 0 ;
  SommeRandom[i]=0 ;
if ( fork() == 0 ){

printf("[son] pid %d from pid [dad] %d \n",getpid (),getppid() ) ;

close(PID[2*i]) ;
dup2(PID[2*i + 1],1);
snprintf(buf,sizeof (buf),"%d",getpid ()) ;
write(PID[2*i + 1],buf,getpid());
close(PID[2*i+1]) ; 
 
exit(i);
}else {
fileCreate(200);
pipe(&PID[2*i+1]);  
if(pipe(&PID[2*i+1])==-1){exit(1);}
close(PID[2*i+1]) ;
dup2(PID[2*i],0);
fatherPIDRead[i]=read(PID[2*i],buf,sizeof(buf));
close(PID[2*i]); 
}
} 
for( int j = 1 ;j<100;j++){
sleep(1) ;
printf(BLU "======================== ON %d second======================== \n" RESET ,j ) ;
for( int i = 1; i <= numChild; i++) {
pipe(&RandomPIP[2*i]);
if(wait(&status)>0) { 
status = WEXITSTATUS(status) ;
if(status > 0){
if(fork() == 0)
{
close(RandomPIP[2*i]) ;
dup2(RandomPIP[2*i +1],1);
random = randomvalue(1,9) ;
write(RandomPIP[2*i+ 1],buf2,random);
close(RandomPIP[2*i+1]) ;
if(pipe(&RandomPIP[2*i])==-1){printf("ERR\n");exit(1);}
exit(i) ;
}else{
if(fatherPIDRead[i]!=10){
pipe(&RandomPIP[2*i+1]);  
close(RandomPIP[2*i+1]) ;
dup2(RandomPIP[2*i],0); 
fatherRandomRead[i]=read(RandomPIP[2*i],buf2,sizeof(buf2));
if(fatherPIDRead[i]!=10){
childWrite(fileCreate(200),fatherRandomRead[i],fatherPIDRead[i]);
printf("son [ %d ] send [ %zd ] \n",fatherPIDRead[i] ,fatherRandomRead[i]) ;
SommeRandom[i] = fatherRandomRead[i] + SommeRandom[i] ;
close(RandomPIP[2*i]);
}
}
}
}
if(SommeRandom[i]>100){
if(fatherPIDRead[i]!=10){
depacement[i] = SommeRandom[i] - 100 ;
kill(fatherPIDRead[i],SIGSTOP);
printf(RED "=============son [ %d ] is Dead with depacement %d \n"RESET , fatherPIDRead[i], depacement[i]);
second[i] = j ;
childWrite1(fileCreate(200),depacement[i],fatherPIDRead[i]);
deadPID[i] = fatherPIDRead[i] ;
fatherPIDRead[i]=10;
dead ++ ;

}
}
}
if(dead== numChild){
break ;
}
}
if(dead== numChild){
break ;
}
}
  for(int i=1 ;i<=numChild;i++){
   sommedepacement=sommedepacement+depacement[i] ;
  }
  moyendepacement= (sommedepacement) / (numChild) ;
  printf("\n") ;
  printf(WHT "======================== All child dead ===========================\n" RESET);
  printf("\n") ;
  printf("\n") ;
  printf("\n") ;
  printf("\n") ;
  printf(WHT"***************** rapport ********************* "RESET);
 printf("\n") ;
  printf("\n") ;
printf(WHT"dad create %d son \n"RESET, numChild) ;
for(int i =1; i<= numChild ; i++){
printf(WHT"on second %d  son [%d] is dead with depacement [%d] \n"RESET,second[i] ,deadPID[i],depacement[i]) ;
}
printf(WHT "moyendepacement is %f \n"RESET ,moyendepacement) ;

}







