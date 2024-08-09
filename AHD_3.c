#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024

void saveTextToFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo para escribir");
        return;
    }
    fprintf(file, "%s", text);
    fclose(file);
}

void saveTextToBinaryFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error al abrir el archivo binario para escribir");
        return;
    }
    size_t length = strlen(text) + 1;
    fwrite(&length, sizeof(size_t), 1, file);
    fwrite(text, sizeof(char), length, file);
    fclose(file);
}

void readTextFromFile(char *buffer, size_t size) {
    printf("Introduce el texto (máximo %zu caracteres):\n", size - 1);
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

int main() {
    int option;
    char text[MAX_LENGTH];

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar texto\n");
        printf("2. Crear archivo binario con el texto ingresado\n");
        printf("3. Crear archivo .txt con el texto ingresado\n");
        printf("4. Salir\n");
        printf("Selecciona una opción: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                readTextFromFile(text, sizeof(text));
                printf("Texto ingresado guardado en memoria.\n");
                break;

            case 2:
                saveTextToBinaryFile("texto.bin", text);
                printf("Archivo binario 'texto.bin' creado.\n");
                break;

            case 3:
                saveTextToFile("texto.txt", text);
                printf("Archivo de texto 'texto.txt' creado.\n");
                break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción no válida. Intenta de nuevo.\n");
                break;
        }
    } while (option != 4);
}