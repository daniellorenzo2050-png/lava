#!/bin/bash

echo "=========================================="
echo "   Instalador Oficial da Linguagem Lava   "
echo "=========================================="

# 1. Verifica se o compilador GCC está disponível
if ! command -v gcc &> /dev/null; then
    echo "[Erro] O GCC não foi encontrado. Instale-o antes de continuar."
    exit 1
fi

echo "[1/3] Compilando o compilador lavac..."
gcc lavac.c -o lavac -Wall

if [ $? -ne 0 ]; then
    echo "[Erro] Falha na compilação do lavac."
    exit 1
fi

# 2. Configura o alias no .bashrc de forma segura
CWD=$(pwd)
HOME_DIR=$HOME
BASHRC_PATH="$HOME_DIR/.bashrc"

echo "[2/3] Configurando variáveis de ambiente no .bashrc..."

# Remove entradas antigas do lavac para evitar duplicidade
if [ -f "$BASHRC_PATH" ]; then
    grep -v "alias lavac=" "$BASHRC_PATH" > "${BASHRC_PATH}.tmp" && mv "${BASHRC_PATH}.tmp" "$BASHRC_PATH"
fi

# Adiciona o novo atalho apontando para o diretório atual
echo "alias lavac='$CWD/lavac'" >> "$BASHRC_PATH"

echo "[3/3] Instalação concluída com sucesso!"
echo "------------------------------------------"
echo "👉 Para ativar os comandos, execute no seu terminal:"
echo "   source ~/.bashrc"
echo "=========================================="
