#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int radius = 5; 
float globalArea = 0;
float pi = 3.141592;

char buf[] = "Calculating the area of a circle using parent and child processes.\n";
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
        sleep(1);
        printf("The child is doing its work...\n");
        sleep(1);
        printf("The child sees the radius of the circle is %d...\n", radius);
        sleep(1);
        float area = (radius*radius)*pi;
        printf("The child calculates the area of this circle and writes the result to a variable that the parent can also access...\n");
        sleep(1);
        globalArea = area;
    }
    else{
        // parent
        if(wait(NULL)>0){
            printf("The child is done executing, this is the parent process speaking.\n");
            sleep(1);
            printf("The area of the triangle calculated by the child was: %f.\n",globalArea);
            sleep(1);
        }
    }
    exit(0);
}
