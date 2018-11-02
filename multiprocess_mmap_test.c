#include<sys/mman.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <string.h>

typedef  struct {
    char name[32];
    int age;
}HUMAN;

int main(int argc, char **argv)
{
    int fd;
    HUMAN *psman;
    if(argc!=2)
    {
        printf("use: map file\n");
        return -1;
    }

    fd = open(argv[1], O_CREAT|O_RDWR, 00777);
    psman = (HUMAN*)mmap(NULL, sizeof(HUMAN)*5, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    for(int i =0; i< 5;i++)
    {
        printf("name:%s age :%d \n",(*(psman+i)).name,(*(psman+i)).age);
    }
    munmap(psman, sizeof(HUMAN)*5);
    printf("unmap over >>>>\n");

    return 0;
}
