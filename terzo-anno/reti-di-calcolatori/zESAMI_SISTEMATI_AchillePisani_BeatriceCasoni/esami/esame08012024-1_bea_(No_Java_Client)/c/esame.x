/*
/// Author:Beatrice Casoni
/// Matricola: 0001079099
*/

const MAX_NAME_SIZE = 256;
const MAX_LIST_SIZE = 7;

struct NomeFile{
	char nome[MAX_NAME_SIZE];
};

struct InputConta {
    char fileName[MAX_NAME_SIZE];
    
};

struct OutputLista {
    NomeFile files[MAX_LIST_SIZE];
    int numFiles;
    int status;
};

struct InputLista {
    char dirName[MAX_LIST_SIZE];
    char carattere;
    int numOccorrenze;
};

program ESAME_PROG {
    version ESAME_VERS {
        int elimina_occorrenze(InputConta ) = 1;
        struct OutputLista lista_file_caratteri(InputLista) = 2;
    } = 1;
} = 0x20000014;