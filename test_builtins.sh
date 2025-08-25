#!/bin/bash

# ============================================================================ #
# SCRIPT DE TESTE PARA BUILT-INS ESSENCIAIS - DIA 10/08
# ============================================================================ #

echo "=== TESTANDO BUILT-INS ESSENCIAIS ==="
echo

echo "1. Testando comando PWD:"
echo "pwd"
echo

echo "2. Testando comando ECHO sem argumentos:"
echo "echo"
echo

echo "3. Testando comando ECHO com argumentos:"
echo "echo Hello World"
echo

echo "4. Testando comando ECHO com flag -n:"
echo "echo -n Hello World"
echo

echo "5. Testando comando ECHO com múltiplas flags -n:"
echo "echo -n -nn -nnn Hello World"
echo

echo "6. Testando comando CD para diretório home:"
echo "cd"
echo "pwd"
echo

echo "7. Testando comando CD para diretório específico:"
echo "cd /tmp"
echo "pwd"
echo

echo "8. Testando comando CD com argumento -:"
echo "cd -"
echo "pwd"
echo

echo "9. Testando comando CD com muitos argumentos (deve dar erro):"
echo "cd /tmp /home /usr"
echo

echo "10. Testando comando CD para diretório inexistente (deve dar erro):"
echo "cd /pasta/que/nao/existe"
echo

echo "=== COMANDOS PLACEHOLDER (implementar domingo) ==="
echo "export TEST=valor"
echo "unset TEST"
echo "exit"
echo

echo "=== TESTE MANUAL ==="
echo "Execute estes comandos no seu minishell para verificar:"
echo "1. pwd"
echo "2. echo Hello World"  
echo "3. echo -n Hello World"
echo "4. cd /tmp && pwd"
echo "5. cd - && pwd"
echo "6. cd ~ && pwd"