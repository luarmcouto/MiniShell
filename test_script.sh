#!/bin/bash

echo "=== Testando strings vazias no MINISHELL ==="
echo ""

# Teste 1
echo "Teste 1: echo hello ''"
echo "echo hello '' | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 2
echo "Teste 2: echo hello '' world"
echo "echo hello '' world | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 3
echo "Teste 3: echo '' hello"
echo "echo '' hello | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 4
echo "Teste 4: echo '' '' ''"
echo "echo '' '' '' | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 5
echo "Teste 5 (normal): echo hello world"
echo "echo hello world | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

echo "=== COMPARAÇÃO COM BASH ==="
echo ""

# Teste 1 - Comparação
echo "Teste 1: echo hello ''"
echo "BASH:"
echo hello '' | cat -A
echo "MINISHELL:"
echo "echo hello '' | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 2 - Comparação
echo "Teste 2: echo hello '' world"
echo "BASH:"
echo hello '' world | cat -A
echo "MINISHELL:"
echo "echo hello '' world | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 3 - Comparação
echo "Teste 3: echo '' hello"
echo "BASH:"
echo '' hello | cat -A
echo "MINISHELL:"
echo "echo '' hello | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 4 - Comparação
echo "Teste 4: echo '' '' ''"
echo "BASH:"
echo '' '' '' | cat -A
echo "MINISHELL:"
echo "echo '' '' '' | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

# Teste 5 - Comparação
echo "Teste 5: echo hello world"
echo "BASH:"
echo hello world | cat -A
echo "MINISHELL:"
echo "echo hello world | cat -A" | ./minishell 2>&1 | grep -v "minishell"
echo ""

echo "=== TESTES COM WC (contagem de caracteres) ==="
echo ""

# Teste com wc
echo "Teste: echo '' 'text' ''"
echo "BASH:"
bash -c "echo '' 'text' '' | wc -c"
echo "MINISHELL:"
echo "echo '' 'text' '' | wc -c" | ./minishell 2>&1 | grep "^[0-9]"
echo ""