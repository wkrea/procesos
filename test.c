/*
obtener acceso a algunas funciones y constantes de la biblioteca C Standard.
*/
#include <stdio.h>  // perror()
#include <stdlib.h> // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h> // fork()

void child() {
    printf("Proceso hijo <%ld>:", (long) getpid()); 
    printf("He iniciado! \n");
    printf("\tMi PID es <%ld> (id propio)\n\tMi PPID <%ld>.(id del padre)\n",
            (long) getpid(), (long) getppid());
    printf("Proceso hijo <%ld> Me despido!\n", (long) getpid());
    exit(EXIT_SUCCESS);
}

void parent(pid_t pid) {
    printf("****************************************************************************");
    printf("Proceso Padre <%ld>: \n",(long) getpid());
    printf("\tMi PID es <%ld> (id propio)\n\tretorno fork() <%ld>.(existe bifurcación)\n",
            (long) getpid(), (long) pid);
    printf("Proceso Padre <%ld> Me despido!\n", (long) getpid());
    exit(EXIT_SUCCESS);
}

void parent_wait1(pid_t pid) {
    printf("Proceso Padre <%ld> generó un un hijo con PID = %ld.\n",
            (long) getpid(), 
            (long) pid);
    wait(NULL);
    printf("Proceso Padre <%ld> hijo con PID = %ld terminó.\n",
            (long) getpid(), 
            (long) pid);
    printf("Proceso Padre <%ld> Goodbye.\n", (long) getpid());
    exit(EXIT_SUCCESS);
}

void parent_wait2(pid_t pid) {
    int status;
    printf("Proceso Padre <%ld> generó un un hijo con PID = %ld.\n",
        (long) getpid(), (long) pid);
    wait(&status);
    if (WIFEXITED(status)) {
    printf("Proceso Padre <%ld> Child with PID = %ld and exit status = %d terminated.\n",
            (long) getpid(), 
            (long) pid, WEXITSTATUS(status));
    }
    printf("PARENT <%ld> Goodbye.\n", (long) getpid());
    exit(EXIT_SUCCESS);
}

void zombie(pid_t pid) {
    printf("Proceso Padre <%ld> generó un un hijo con PID = %ld.\n",
        (long) getpid(), (long) pid);
    printf("Proceso Padre <%ld>: Presione una tecla para engendrar zombies!!! jajajaj\n",
        (long) getpid());
    getchar();
    pid=wait(NULL);
    printf("Proceso Padre <%ld>: un zombie con PID = %ld fue engendrado\n", (long) getpid(), (long) pid);
    exit(EXIT_SUCCESS);
}



int main(void) {

    pid_t pid;
    // Invocar de fork()
    switch (pid = fork()) {

        // Verificar el retorno, para saber si se crearomn procesos bifurcados (hijos)
        case -1:
            // Esto se presenta cuando fork() returns -1.
            perror("fork failed");
            exit(EXIT_FAILURE);

        case 0:
            // En caso exitoso fork() returns 0.
            
            // Aqui estan las instrucciones que el hijo ejecutara
            child();

        default:
            // si el retorno de fork() es distinto de error o del identificador del hijo.
            
            // Aqui estan las instrucciones que el padre ejecutara
            parent(pid);
    }
 }
