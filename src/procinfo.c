#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static void usage(const char *a){fprintf(stderr,"Usage: %s <pid>\n",a); exit(1);}
static int isnum(const char*s){for(;*s;s++) if(!isdigit(*s)) return 0; return 1;}
int main(int c,char**v){
 if(c!=2||!isnum(v[1])) usage(v[0]);
 
 char processState;
 int ppid;
 char cmdline[100];
 int utime;
 int stime;


 long pid = strtoll(v[1], NULL, 10);
 if (pid==0) {
    printf("Invalid pid\n");
    exit(0);
 }

 FILE *statptr;
 char filepath[100];
 sprintf(filepath, "../../../../../../proc/%ld/stat", pid);

 statptr = fopen(filepath,"r");
 if (statptr==NULL){
    printf("pid not found\n");
    exit(0);
 }
 fscanf(statptr, "%*d %*s %c %d %d %d", &processState, &ppid, &utime, &stime);

 FILE *cmdptr;
 sprintf(filepath, "../../../../proc/%ld/cmdline", pid);
 cmdptr = fopen(filepath,"r");
 if (cmdptr==NULL) {
    printf("pid not found\n");
    exit(0);
 }
 fgets(cmdline, 100, cmdptr);

 printf("PID:%ld\nState:%c\nPPID:%d\nCmdline:%s\nUtime:%d\nStime:%d\n", pid, processState, ppid, cmdline, utime, stime);

 fclose(cmdptr);
 fclose(statptr);
 return 0;
}
