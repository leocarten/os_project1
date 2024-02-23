#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int base = 3; 
int height = 4;
float globalArea = 0;

char buf[] = "Calculating the area of a triangle using parent and child processes\n";
int main(){
    pid_t pid;
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1){
        printf("write error");
        exit(1);
    }
    if ( (pid = vfork()) < 0){
        printf("fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        // child
        printf("The child is doing its work...\n");
        sleep(1);
        printf("The child sees the base of the triangle is %d, and the height is %d...\n", base, height);
        sleep(1);
        float area = (height*base)/2;
        printf("The child calculates the area of this triangle is: %f\n", area);
        sleep(1);
        globalArea = area;
    }
    else{
        // parent
        if(wait(NULL)>0){
            printf("The child is done executing, this is the parent process speaking.\n");
            sleep(1);
            printf("The area of the triangle is: %f\n",globalArea);
        }
    }
    exit(0);
}
