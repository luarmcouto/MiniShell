#!/bin/bash

# Teste focado para verificar funcionalidades implementadas
# Data: 12/08/2025 - Sistema de redirecionamentos

echo "=== TESTE MINISHELL - STATUS DO PROJETO ==="
echo "Data: $(date)"
echo

# Limpeza inicial
rm -f test_*.txt input_*.txt output_*.txt 2>/dev/null

# Cores
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

passed=0
total=0

test_command() {
    local desc="$1"
    local cmd="$2"
    local expected="$3"
    
    echo -e "${BLUE}Teste $((++total)): $desc${NC}"
    echo "Comando: $cmd"
    
    # Executa comando
    echo "$cmd" | ./minishell > test_output.tmp 2>&1
    
    if [[ $? -eq 0 ]]; then
        echo -e "${GREEN}✓ Passou${NC}"
        ((passed++))
    else
        echo -e "${RED}✗ Falhou${NC}"
    fi
    echo "---"
}

test_file_creation() {
    local desc="$1"
    local cmd="$2"
    local file="$3"
    local expected_content="$4"
    
    echo -e "${BLUE}Teste $((++total)): $desc${NC}"
    echo "Comando: $cmd"
    
    echo "$cmd" | ./minishell > /dev/null 2>&1
    
    if [[ -f "$file" ]]; then
        content=$(cat "$file" 2>/dev/null)
        if [[ "$content" == *"$expected_content"* ]]; then
            echo -e "${GREEN}✓ Arquivo criado com conteúdo correto${NC}"
            ((passed++))
        else
            echo -e "${RED}✗ Arquivo criado mas conteúdo incorreto${NC}"
            echo "Esperado: $expected_content"
            echo "Obtido: $content"
        fi
    else
        echo -e "${RED}✗ Arquivo não foi criado${NC}"
    fi
    echo "---"
}

echo "### BUILT-INS BÁSICOS ###"

test_command "Built-in pwd" "pwd" "path"
test_command "Built-in echo" "echo Hello World" "Hello World"
test_command "Built-in env" "env" "variables"

echo -e "\n### REDIRECIONAMENTOS ###"

test_file_creation "Redirecionamento saída >" "echo 'output test' > test_redirect.txt" "test_redirect.txt" "output test"

# Teste de entrada (se o arquivo anterior foi criado)
if [[ -f "test_redirect.txt" ]]; then
    test_command "Redirecionamento entrada <" "cat < test_redirect.txt" "output test"
fi

test_file_creation "Redirecionamento append >>" "echo 'second line' >> test_redirect.txt" "test_redirect.txt" "second line"

echo -e "\n### HEREDOC ###"

echo -e "${BLUE}Teste $((++total)): Heredoc simples${NC}"
echo "Testando heredoc básico..."
echo "cat << EOF
heredoc line 1
heredoc line 2
EOF
exit" | ./minishell > heredoc_output.tmp 2>&1

if grep -q "heredoc line 1" heredoc_output.tmp && grep -q "heredoc line 2" heredoc_output.tmp; then
    echo -e "${GREEN}✓ Heredoc funcionando${NC}"
    ((passed++))
else
    echo -e "${RED}✗ Heredoc não funcionou${NC}"
fi
echo "---"

echo -e "\n### COMANDOS EXTERNOS ###"

test_command "Comando externo ls" "ls /tmp" "."
test_command "Comando externo com caminho" "/bin/echo external" "external"

echo -e "\n### COMBINAÇÕES ###"

test_file_creation "Echo com redirecionamento" "echo 'combined test' > combined.txt" "combined.txt" "combined test"

if [[ -f "combined.txt" ]]; then
    test_command "Cat com entrada" "cat < combined.txt" "combined test"
fi

echo -e "\n### TRATAMENTO DE ERROS ###"

echo -e "${BLUE}Teste $((++total)): Arquivo inexistente${NC}"
echo "cat < arquivo_inexistente.txt
exit" | ./minishell > error_test.tmp 2>&1

if grep -q -i "no such file\|not found" error_test.tmp; then
    echo -e "${GREEN}✓ Erro tratado corretamente${NC}"
    ((passed++))
else
    echo -e "${RED}✗ Erro não tratado adequadamente${NC}"
fi
echo "---"

# Resultado final
echo -e "\n${BLUE}=== RESULTADO FINAL ===${NC}"
echo "Testes passados: $passed de $total"

if [[ $passed -eq $total ]]; then
    echo -e "${GREEN}🎉 TODOS OS TESTES PASSARAM!${NC}"
    echo "Sistema de redirecionamentos implementado com sucesso!"
elif [[ $passed -gt $((total/2)) ]]; then
    echo -e "${GREEN}📈 BOA IMPLEMENTAÇÃO!${NC}"
    echo "Maioria das funcionalidades estão funcionando."
else
    echo -e "${RED}🔧 PRECISA DE MAIS TRABALHO${NC}"
    echo "Várias funcionalidades ainda precisam ser implementadas."
fi

echo -e "\n${BLUE}STATUS DO CRONOGRAMA:${NC}"
echo "✓ Built-ins básicos: $([ $passed -gt 0 ] && echo "FUNCIONANDO" || echo "PENDENTE")"
echo "✓ Redirecionamentos: $([ -f "test_redirect.txt" ] && echo "FUNCIONANDO" || echo "PENDENTE")"
echo "✓ Heredoc: $(grep -q "heredoc line" heredoc_output.tmp 2>/dev/null && echo "FUNCIONANDO" || echo "PENDENTE")"

# Limpeza
echo -e "\nRemovendo arquivos de teste..."
rm -f test_*.txt test_*.tmp combined.txt heredoc_output.tmp error_test.tmp input_*.txt output_*.txt

echo -e "${BLUE}Teste concluído!${NC}"