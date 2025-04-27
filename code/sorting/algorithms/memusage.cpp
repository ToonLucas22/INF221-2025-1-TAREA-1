#include "stdlib.h"
#include "stdio.h"
#include "string.h"

int curMemUsage;

/*
    Las siguientes funciones parseLine y getValue han sido tomadas
    de esta página de stackoverflow:
    https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process

    Su propósito es parsear el valor arrojado por el kernel correspondiente
    a la memoria usada por el proceso actual y luego retornar tal valor.
*/

int parseLine(char* line){
    // Asume que un dígito será encontrado y que la línea termina en " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Nota: Este valor está en kilobytes
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}
