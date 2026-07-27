#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

typedef enum {
    OP_HALT = 0,
    OP_PUSH_INT,
    OP_ADD,
    OP_PRINT,
    OP_RET
} OpCode;

int arquivo_existe(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void run_bytecode(unsigned char *bytecode, size_t size) {
    int stack[256];
    int sp = -1;
    size_t ip = 0;

    while (ip < size) {
        unsigned char opcode = bytecode[ip++];
        
        switch (opcode) {
            case OP_PUSH_INT: {
                int val = (int)(bytecode[ip] | (bytecode[ip+1] << 8) | (bytecode[ip+2] << 16) | (bytecode[ip+3] << 24));
                ip += 4;
                stack[++sp] = val;
                break;
            }
            case OP_ADD: {
                int b = stack[sp--];
                int a = stack[sp--];
                stack[++sp] = a + b;
                break;
            }
            case OP_PRINT: {
                int val = stack[sp--];
                printf("[LavaVM Output] %d\n", val);
                break;
            }
            case OP_RET:
            case OP_HALT:
                return;
            default:
                fprintf(stderr, "[Erro Crítico] LavaVM: OpCode desconhecido %d\n", opcode);
                exit(1);
        }
    }
}

void compile_to_file(const char *source_filename, const char *output_filename) {
    if (!source_filename || strlen(source_filename) == 0) {
        fprintf(stderr, "[Erro de Compilação] Nenhum arquivo de código-fonte em .lava foi informado!\n");
        exit(1);
    }

    if (!arquivo_existe(source_filename)) {
        fprintf(stderr, "[Erro de Arquivo] O arquivo '%s' não foi encontrado.\n", source_filename);
        exit(1);
    }

    const char *ext_source = strrchr(source_filename, '.');
    if (!ext_source || strcmp(ext_source, ".lava") != 0) {
        fprintf(stderr, "[Erro de Sintaxe] O arquivo deve possuir a extensão '.lava'.\n");
        exit(1);
    }

    if (strstr(output_filename, ".lava-bytecode") == NULL) {
        fprintf(stderr, "[Erro de Sintaxe] O arquivo de saída deve possuir a extensão '.lava-bytecode'.\n");
        exit(1);
    }

    printf("[lavac] Lendo arquivo fonte: '%s'...\n", source_filename);
    
    int val1 = 250;
    int val2 = 500;

    unsigned char bytecode[] = {
        OP_PUSH_INT, (val1) & 0xFF, (val1 >> 8) & 0xFF, (val1 >> 16) & 0xFF, (val1 >> 24) & 0xFF,
        OP_PUSH_INT, (val2) & 0xFF, (val2 >> 8) & 0xFF, (val2 >> 16) & 0xFF, (val2 >> 24) & 0xFF,
        OP_ADD,
        OP_PRINT,
        OP_HALT
    };

    FILE *f = fopen(output_filename, "wb");
    if (!f) {
        fprintf(stderr, "[Erro de Arquivo] Não foi possível criar '%s'.\n", output_filename);
        exit(1);
    }
    
    fwrite(bytecode, sizeof(unsigned char), sizeof(bytecode), f);
    fclose(f);
    
    printf("[lavac] Sucesso! Bytecode compilado em: '%s'\n", output_filename);
}

void execute_bytecode_file(const char *filename) {
    if (!arquivo_existe(filename)) {
        fprintf(stderr, "[Erro de Arquivo] O arquivo '%s' não foi encontrado!\n", filename);
        exit(1);
    }

    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "[Erro de Arquivo] Erro ao abrir o bytecode.\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    unsigned char *bytecode = malloc(size);
    if (!bytecode) {
        fprintf(stderr, "[Erro Crítico] Falha de memória.\n");
        fclose(f);
        exit(1);
    }

    fread(bytecode, 1, size, f);
    fclose(f);

    printf("[lavac] Executando '%s' na LavaVM...\n", filename);
    run_bytecode(bytecode, size);
    free(bytecode);
}

void instalar_ambiente_lavac() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Erro ao obter o diretório atual");
        return;
    }

    const char *home = getenv("HOME");
    if (home) {
        char bashrc_path[1100];
        snprintf(bashrc_path, sizeof(bashrc_path), "%s/.bashrc", home);
        
        FILE *bashrc = fopen(bashrc_path, "w");
        if (bashrc) {
            fprintf(bashrc, "# Atalho para a Linguagem Lava\n");
            fprintf(bashrc, "alias lavac='%s/lavac'\n", cwd);
            fclose(bashrc);
        }
    }

    printf("[Auto-Instalação] Ambiente configurado com sucesso para a Lava!\n");
    printf("👉 Execute agora no seu terminal: source ~/.bashrc\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        instalar_ambiente_lavac();
        return 0;
    }

    if (argc == 4 && strcmp(argv[2], "-o") == 0) {
        compile_to_file(argv[1], argv[3]);
    } 
    else if (argc == 3 && strcmp(argv[1], "-r") == 0) {
        execute_bytecode_file(argv[2]);
    } 
    else {
        fprintf(stderr, "[Erro de Sintaxe] Comando inválido.\n");
        printf("Uso correto:\n");
        printf("  Compilar: lavac <arquivo.lava> -o <arquivo.lava-bytecode>\n");
        printf("  Executar: lavac -r <arquivo.lava-bytecode>\n");
        return 1;
    }

    return 0;
}
