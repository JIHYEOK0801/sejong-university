#include <stdio.h>
#define BUFSIZE 512
int main(){
    FILE *fp;
    printf("testdata를 입력하세요 : ");
    fp = fopen("testdata", "w+");

    char testdata[100];
    gets(testdata);
    fputs(testdata, fp);

    int offset;
    char rbuf[1];
    while(1){
        printf("current offset : ");
        scanf("%d", &offset);

        fseek(fp, (offset) * sizeof(char), SEEK_SET);
        fread(rbuf, sizeof(char), 1, fp);
        printf("  current data : %c\n", rbuf[0]);
    }
}
