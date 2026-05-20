#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;  
    }
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        printf("Collatz sequence: ");
        while (n != 1) {
            printf("%d ", n);

            if (n % 2 == 0)
                n = n / 2;
            else
                n = 3 * n + 1;
        }
        printf("%d\n", n);

        exit(0);
    }else {
        wait(NULL); 
        printf("Child process finished.\n");
    }
    return 0;
}
