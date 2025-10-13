/*
/// Author:Beatrice Casoni
/// Matricola: 0001079099
*/

#include "esame.h"
#include <dirent.h>
#include <fcntl.h>
#include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define DIM_BUFF 1024

/********************************************************/
/* SERVIZIO 1 ========================================== */

int *elimina_occorrenze_1_svc(InputConta *request, struct svc_req *rqstp) {
    /* Variabili ---------------------------------------- */
    
    static int response;
    response = 0;
    char buffer[DIM_BUFF];
    int bytes_read;
    int uguale = 0;
    char nuovo_contenuto[1024];
    int temp_fd;

    /* Logica di business ------------------------------- */

    printf("\nConto occorrenze di car alfabetici nel file da eliminare %s\n", request-> fileName);

    // Algoritmo ------------------------------------------------
    int fd = open(request-> fileName, O_RDONLY);
    if (fd < 0) {
        perror("Errore apertura file");
        response = -1;
        return (&response);
    }

    // Creazione file temporaneo
    char temp_filename[] = "/tmp/tempfileXXXXXX";
    temp_fd = mkstemp(temp_filename);
    if (temp_fd < 0) {
        perror("creazione file temporaneo");
        close(fd);
        response = -1;
        return (&response);
    }

    int index = 0;
	while((bytes_read = read(fd, buffer, DIM_BUFF)) > 0)
	{
		for(int i = 0; i < bytes_read; i++)
		{
			char c = buffer[i];
            if(!Character.isalpha(c)){
                if (write(temp_fd, &buffer[i], 1) < 0) {
                    perror("write");
                    close(fd);
                    close(temp_fd);
                    unlink(temp_filename);
                    response = -2;
                    return (&response);
                }
            }else
                response++;
		}
	}

    if (bytes_read < 0) {
        perror("Errore lettura file");
        close(fd);
        response = -2;
        return (&response);
    }

     close(fd);
    close(temp_fd);

    // Rinomino il file temporaneo
    if (rename(temp_filename, request->filename) < 0) {
        perror("rename");
        unlink(temp_filename);
        response = -2;
        return (&response);
    }
    /* Fine logica di business --------------------------- */

    return (&response);
}

/* SERVIZIO 2 ========================================== */

OutputLista *lista_file_caratteri_1_svc(InputLista *request, struct svc_req *rqstp) {
    /* Variabili ---------------------------------------- */

    static OutputLista response;
    response.numFiles = 0;
    response.status = 0;
    struct dirent *entry;
    int presente;
    int countOcc = 0;

    /* Logica di business ------------------------------- */

    printf("Listo file con della directory %s\n", request -> dirName);

    // Algoritmo -----------------------------------------------------
    DIR *dir = opendir(request -> dirName);
    if (dir == NULL) {
        perror("Errore nell'aprire la directory");
        response.status = -1;
        return (&response);
    }

    while ((entry = readdir(dir)) != NULL ) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        printf("Analizzo %s\n", entry->d_name);

        presente = 0;
        // if (strncmp(entry->d_name, request -> prefisso, strlen(request -> prefisso)) == 0) {
        //     presente++;
        // }

        for(int i = 0, i < strlen(entry->d_name); i++){
            if(entry->d_name[i] == request->carattere)
            {
                countOcc++;
            }
        }
        if(countOcc >= request->numOccorrenze && response.numFiles <= MAX_LIST_SIZE){
            strcpy(response.files[response.numFiles].nome, entry->d_name); 
            response.numFiles ++;
        }
        
        // if ( presente > 0 && response.numFiles <= MAX_LIST_SIZE ){
        //     strcpy(response.files[response.numFiles].nome, entry->d_name); 
        //     response.numFiles ++;
        // }
    }
    closedir(dir);

    /* Fine logica di business --------------------------- */

    return (&response);
}
