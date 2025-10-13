/*
/// Author: Beatrice Casoni
/// Matricola: 0001079099
*/

const MAX_FILE_NAME = 40;
const MAX_FILE_LIST = 11;
const MAX_PAROLA = 9;

struct FileName{
	char name[MAX_FILE_NAME];
};

struct InputElimina {
    char fileName[MAX_FILE_NAME];
    char parolaUtente[MAX_PAROLA];
};

struct InputLista {
    char dirName[MAX_FILE_NAME];
    int soglia;
};

struct OutputLista {
    FileName nomiFile[MAX_FILE_LIST];
    int numFile;
    int status;
};

struct OutputElimina {
    int numEliminati;
};

program ESAME_PROG {
    version ESAME_VERS {
        struct OutputLista LISTA_NOMIFILE_SOGLIA(InputLista) = 1;
        struct OutputElimina ELIMINA_PAROLA(InputElimina) = 2;
    } = 1;
} = 0x20000014;