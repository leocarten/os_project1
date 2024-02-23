#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define pi 3.1415

int main() {
    pid_t pid, pid1, pid2;
    int radius = 5;
    int side = 4;
    int base = 4;
    int height = 3;
    float globalArea, globalArea1, globalArea2;
    char buf[] = "Calculating area using parent and child processes.\n";
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
        printf("write error");
        exit(1);
    }
    if ((pid = vfork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        // child - circle
        sleep(1);
        printf("The circle child is doing its work...\n");
        sleep(1);
        printf("The circle child sees the radius of the circle is %d...\n", radius);
        sleep(1);
        float area = (radius * radius) * pi;
        printf("The circle child calculates the area of this circle and writes the result to a variable that the parent can also access...\n");
        sleep(1);
        globalArea = area;
        exit(0);
    }

    if ((pid1 = vfork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid1 == 0) {
        // child - square
        sleep(1);
        printf("The square child is doing its work...\n");
        sleep(1);
        printf("The square child sees the side of the square is %d...\n", side);
        sleep(1);
        float area = (side * side);
        printf("The square child calculates the area of this square and writes the result to a variable that the parent can also access...\n");
        sleep(1);
        globalArea1 = area;
        exit(0);
    }

    if ((pid2 = vfork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid2 == 0) {
        // child - triangle
        sleep(1);
        printf("The triangle child is doing its work...\n");
        sleep(1);
        printf("The triangle child sees the base of the triangle is %d, and the height is %d...\n", base, height);
        sleep(1);
        float area = (height * base) / 2;
        printf("The triangle child calculates the area of this triangle and writes the result to a variable that the parent can also access...\n");
        sleep(1);
        globalArea2 = area;
        exit(0);
    } else {
        // parent
        while (wait(NULL) > 0);
        sleep(1);
        printf("The children are done executing, this is the parent process speaking.\n");
        sleep(1);
        printf("The area of the circle calculated by the child was: %f.\n", globalArea);
        printf("The area of the square calculated by the child was: %f.\n", globalArea1);
        printf("The area of the triangle calculated by the child was: %f.\n", globalArea2);
    }

    exit(0);
}
