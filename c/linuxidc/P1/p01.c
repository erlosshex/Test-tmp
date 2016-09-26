/* example.c */
#include <stdio.h>
#include <string.h>

void bzero(char *buf, int n);

int main()
{
    char buf[100];
    bzero(buf,100);
    fgets(buf,100,stdin);
    printf("you have input %d letter\n",strlen(buf));
    return 0;
}


void bzero(char *buf, int n)
{
    int i=0;
    for(i=0;i<n;++i){
        buf[i]=0;
    }
}

