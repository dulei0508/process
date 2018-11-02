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
    fd = open(argv[1], O_CREAT|O_RDWR|O_TRUNC, 00777);
    lseek(fd, sizeof(HUMAN)*3-1, SEEK_SET);
    write(fd, "ok", sizeof("ok"));
    psman = (HUMAN*)mmap(NULL, sizeof(HUMAN)*5, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    HUMAN xiao = {"xiaoming", 20};
    HUMAN chen = {"chenming", 30};
    HUMAN liu  = {"liuming" , 30};

    memcpy(&psman[0], &liu , sizeof(HUMAN));
    memcpy(&psman[1], &xiao, sizeof(HUMAN));
    memcpy(&psman[2], &chen, sizeof(HUMAN));
    memcpy(&psman[3], &liu, sizeof(HUMAN));
    memcpy(&psman[4], &liu, sizeof(HUMAN));
    printf("init over >>>>\n");
    sleep(10);
    munmap(psman, sizeof(HUMAN)*5);
    printf("unmap over >>>>\n");

    return 0;
}
