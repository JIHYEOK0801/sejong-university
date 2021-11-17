#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
void handler(int signo){
        psignal(signo, "Received Signal");
}

int main(){
        pid_t pid, ppid;
        int fd, pagesize, length;
        caddr_t addr;
        pagesize = sysconf(_SC_PAGESIZE);
        length = 1 * pagesize;

        if((fd = open("m.dat", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1){
                perror("open");
                exit(1);
        }

        if(ftruncate(fd, (off_t)length) == -1){
                perror("fruncate");
                exit(1);
        }

        addr = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
        if(addr == MAP_FAILED){
                perror("mmap");
                exit(1);
        }

        close(fd);

        void (*hand)(int);
        hand = signal(SIGUSR1, handler);
        if(hand == SIG_ERR){
                perror("signal");
                exit(1);
                }

        switch(pid = fork()){
                case -1: /* fork failed */
                        perror("fork");
                        exit(1);
                        break;

                case 0: /*child process */
                        // addr에 메시지를 쓴다.
                        strcpy(addr, "Message from child process to parent process");
                        //시그널을 부모 프로세스에게 보낸다.
                        kill(getppid(), SIGUSR1);
                        break;
                default: /*parent process*/
                        //시그널을 대기한다.
                        pause();
                        //자식이 쓴 메시지 출력한다.
                        printf("자식이 쓴 메시지 출력 : ");
                        printf("%s\n",addr);
                        break;
        }
}