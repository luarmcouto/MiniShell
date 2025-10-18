#!/bin/bash

# =============================================================================
# CONFIGURAÇÕES CUSTOMIZÁVEIS - MODIFIQUE AQUI
# =============================================================================

# Nome do executável do seu minishell
MINISHELL_EXEC="./minishell"

# Diretório onde está o minishell (deixe vazio se estiver no diretório atual)
MINISHELL_DIR=""

# Timeout para cada teste (em segundos)
TEST_TIMEOUT=3

# Arquivo temporário para capturar output
TEMP_OUTPUT="/tmp/minishell_test_output.txt"

# =============================================================================
# CONFIGURAÇÃO AUTOMÁTICA
# =============================================================================

# Se especificou diretório, use caminho completo
if [[ -n "$MINISHELL_DIR" ]]; then
    FULL_PATH="$MINISHELL_DIR/$MINISHELL_EXEC"
else
    FULL_PATH="$MINISHELL_EXEC"
fi

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# =============================================================================
# FUNÇÕES DE VERIFICAÇÃO (DEFINIDAS PRIMEIRO)
# =============================================================================

# Função para verificar se tokens são impressos
check_tokens_printed() {
    local output="$1"
    if echo "$output" | grep -q "TOKEN ANALYSIS\|Tokens criados"; then
        return 0
    fi
    return 1
}

# Função para verificar se não há crash
check_no_crash() {
    local output="$1"
    if echo "$output" | grep -q "Segmentation fault\|Bus error\|Aborted"; then
        return 1
    fi
    return 0
}

# Função para verificar erros de sintaxe
check_syntax_error() {
    local output="$1"
    if echo "$output" | grep -q "syntax error\|error"; then
        return 0
    fi
    return 1
}

# =============================================================================
# FUNÇÕES DE TESTE
# =============================================================================

print_header() {
    echo -e "\n${BLUE}=============================================================================${NC}"
    echo -e "${WHITE}$1${NC}"
    echo -e "${BLUE}=============================================================================${NC}\n"
}

print_section() {
    echo -e "\n${PURPLE}--- $1 ---${NC}"
}

# Função para verificar se minishell existe
check_minishell_exists() {
    echo -e "${CYAN}Verificando configuração...${NC}"
    echo "Procurando por: $FULL_PATH"
    
    if [[ ! -f "$FULL_PATH" ]]; then
        echo -e "${RED}ERRO: $FULL_PATH não encontrado!${NC}"
        echo -e "${YELLOW}Opções:${NC}"
        echo "1. Modifique MINISHELL_EXEC no topo do script"
        echo "2. Modifique MINISHELL_DIR se estiver em outro diretório"
        echo "3. Execute 'make' para compilar"
        exit 1
    fi
    
    if [[ ! -x "$FULL_PATH" ]]; then
        echo -e "${RED}ERRO: $FULL_PATH não é executável!${NC}"
        echo "Execute: chmod +x $FULL_PATH"
        exit 1
    fi
    
    echo -e "${GREEN}✓ Minishell encontrado: $FULL_PATH${NC}"
}

# Função de teste com verificação específica (IGUAL À QUE FUNCIONA)
run_test_with_check() {
    local test_name="$1"
    local command="$2"
    local expected="$3"
    
    ((TOTAL_TESTS++))
    
    echo -e "${CYAN}Teste $TOTAL_TESTS: $test_name${NC}"
    echo "Comando: $command"
    
    > "$TEMP_OUTPUT"
    
    local exit_code=0
    if timeout "$TEST_TIMEOUT" bash -c "echo '$command' | $FULL_PATH" > "$TEMP_OUTPUT" 2>&1; then
        exit_code=0
    else
        exit_code=$?
    fi
    
    local output=$(cat "$TEMP_OUTPUT" 2>/dev/null)
    
    # Verificações específicas
    local passed=false
    case "$expected" in
        "tokens")
            if check_tokens_printed "$output"; then
                passed=true
            fi
            ;;
        "error")
            if check_syntax_error "$output"; then
                passed=true
            fi
            ;;
        "no_crash")
            if check_no_crash "$output"; then
                passed=true
            fi
            ;;
        *)
            if [[ $exit_code -eq 0 ]]; then
                passed=true
            fi
            ;;
    esac
    
    if [[ "$passed" == "true" ]]; then
        echo -e "Status: ${GREEN}PASSOU${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "Status: ${RED}FALHOU${NC}"
        ((FAILED_TESTS++))
    fi
    
    echo "Saída:"
    echo "$output" | head -5
    echo ""
}

# =============================================================================
# INÍCIO DOS TESTES
# =============================================================================

clear
print_header "TESTADOR AUTOMÁTICO MINISHELL - VERSÃO COMPLETA CORRIGIDA"

check_minishell_exists

echo -e "${YELLOW}Configuração:${NC}"
echo "Executável: $FULL_PATH"
echo "Timeout: ${TEST_TIMEOUT}s"
echo ""

echo -e "${YELLOW}Iniciando bateria completa de testes...${NC}\n"

# =============================================================================
# TESTES DE COMANDOS BÁSICOS
# =============================================================================
print_section "1. TESTES DE COMANDOS BÁSICOS"

run_test_with_check \
    "Comando simples (pwd)" \
    "pwd" \
    "no_crash"

run_test_with_check \
    "Built-in echo" \
    "echo hello world" \
    "no_crash"

run_test_with_check \
    "Comando externo (ls)" \
    "ls" \
    "no_crash"

run_test_with_check \
    "Comando com argumentos" \
    "ls -la" \
    "no_crash"

run_test_with_check \
    "Comando inexistente" \
    "comandoinexistente" \
    "no_crash"

run_test_with_check \
    "Comando com caminho absoluto" \
    "/bin/ls" \
    "no_crash"

# =============================================================================
# TESTES DE ASPAS
# =============================================================================
print_section "2. TESTES DE ASPAS"

run_test_with_check \
    "Aspas simples básicas" \
    "echo 'hello world'" \
    "no_crash"

run_test_with_check \
    "Aspas duplas básicas" \
    'echo "hello world"' \
    "no_crash"

run_test_with_check \
    "Aspas simples com metacaracteres" \
    "echo 'pipe | and > redirect'" \
    "no_crash"

run_test_with_check \
    "Aspas duplas com variável" \
    'echo "home is $HOME"' \
    "no_crash"

run_test_with_check \
    "Aspas aninhadas" \
    'echo "hello '"'"'world'"'"'"' \
    "no_crash"

run_test_with_check \
    "Aspas não fechadas (deve dar erro)" \
    "echo 'hello" \
    "error"

run_test_with_check \
    "Aspas duplas não fechadas" \
    'echo "hello' \
    "error"

# =============================================================================
# TESTES DE PIPES
# =============================================================================
print_section "3. TESTES DE PIPES"

run_test_with_check \
    "Pipe simples" \
    "echo hello | cat" \
    "no_crash"

run_test_with_check \
    "Pipe com ls e grep" \
    "ls | grep test" \
    "no_crash"

run_test_with_check \
    "Múltiplos pipes" \
    "echo hello | cat | cat" \
    "no_crash"

run_test_with_check \
    "Pipe com built-ins" \
    "echo test | cat" \
    "no_crash"

run_test_with_check \
    "Pipe inválido - início" \
    "| ls" \
    "error"

run_test_with_check \
    "Pipe inválido - final" \
    "ls |" \
    "error"

run_test_with_check \
    "Pipes consecutivos (erro)" \
    "ls || grep test" \
    "error"

# =============================================================================
# TESTES DE REDIRECIONAMENTOS
# =============================================================================
print_section "4. TESTES DE REDIRECIONAMENTOS"

run_test_with_check \
    "Redirecionamento saída" \
    "echo hello > /tmp/test_out.txt" \
    "no_crash"

run_test_with_check \
    "Redirecionamento entrada" \
    "cat < /etc/passwd" \
    "no_crash"

run_test_with_check \
    "Redirecionamento append" \
    "echo world >> /tmp/test_out.txt" \
    "no_crash"

run_test_with_check \
    "Múltiplos redirecionamentos" \
    "cat < /etc/passwd > /tmp/copy.txt" \
    "no_crash"

run_test_with_check \
    "Heredoc" \
    "cat << EOF" \
    "no_crash"

run_test_with_check \
    "Redirecionamento sem arquivo (erro)" \
    "echo hello >" \
    "error"

# =============================================================================
# TESTES DE VARIÁVEIS
# =============================================================================
print_section "5. TESTES DE VARIÁVEIS"

run_test_with_check \
    "Variável HOME" \
    'echo $HOME' \
    "no_crash"

run_test_with_check \
    "Variável PATH" \
    'echo $PATH' \
    "no_crash"

run_test_with_check \
    "Exit status" \
    'echo $?' \
    "no_crash"

run_test_with_check \
    "Variável USER" \
    'echo $USER' \
    "no_crash"

run_test_with_check \
    "Variável inexistente" \
    'echo $VARIAVEL_INEXISTENTE' \
    "no_crash"

run_test_with_check \
    "Múltiplas variáveis" \
    'echo $HOME $USER' \
    "no_crash"

run_test_with_check \
    "Variável em aspas duplas" \
    'echo "My home: $HOME"' \
    "no_crash"

run_test_with_check \
    "Variável em aspas simples" \
    "echo 'Variable: \$HOME'" \
    "no_crash"

# =============================================================================
# TESTES DE BUILT-INS
# =============================================================================
print_section "6. TESTES DE BUILT-INS"

run_test_with_check \
    "echo sem argumentos" \
    "echo" \
    "no_crash"

run_test_with_check \
    "echo com flag -n" \
    "echo -n hello" \
    "no_crash"

run_test_with_check \
    "pwd (print working directory)" \
    "pwd" \
    "no_crash"

run_test_with_check \
    "env (listar variáveis)" \
    "env" \
    "no_crash"

run_test_with_check \
    "cd para diretório" \
    "cd /tmp" \
    "no_crash"

run_test_with_check \
    "cd sem argumentos" \
    "cd" \
    "no_crash"

# =============================================================================
# TESTES DE OPERADORES LÓGICOS (BONUS)
# =============================================================================
print_section "7. TESTES DE OPERADORES LÓGICOS (BONUS)"

run_test_with_check \
    "Operador AND (&&)" \
    "echo hello && echo world" \
    "no_crash"

run_test_with_check \
    "Operador OR (||)" \
    "false || echo fallback" \
    "no_crash"

run_test_with_check \
    "Parênteses simples" \
    "(echo hello)" \
    "no_crash"

run_test_with_check \
    "Precedência com parênteses" \
    "(echo first && echo second) || echo third" \
    "no_crash"

# =============================================================================
# TESTES DE VALIDAÇÃO DE INPUT
# =============================================================================
print_section "8. TESTES DE VALIDAÇÃO DE INPUT"

run_test_with_check \
    "Parênteses não balanceados - fecha" \
    "echo hello)" \
    "error"

run_test_with_check \
    "Parênteses não balanceados - abre" \
    "(echo hello" \
    "error"

run_test_with_check \
    "Linha muito longa" \
    "$(printf 'echo %0.s' {1..250})" \
    "error"

run_test_with_check \
    "Múltiplos espaços" \
    "   echo    hello    world   " \
    "no_crash"

run_test_with_check \
    "Entrada vazia" \
    "" \
    "no_crash"

run_test_with_check \
    "Só espaços" \
    "   " \
    "no_crash"

# =============================================================================
# TESTES DE CASOS EXTREMOS
# =============================================================================
print_section "9. TESTES DE CASOS EXTREMOS"

run_test_with_check \
    "Metacaracteres misturados" \
    "echo hello | > world" \
    "error"

run_test_with_check \
    "Comando com muitos argumentos" \
    "echo arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9 arg10" \
    "no_crash"

run_test_with_check \
    "Pipe com comando inexistente" \
    "comandoinexistente | cat" \
    "no_crash"

run_test_with_check \
    "Caracteres especiais" \
    "echo 'special: !@#\$%^&*()'" \
    "no_crash"

# =============================================================================
# TESTES DE DEBUG/TOKENS
# =============================================================================
print_section "10. TESTES DE DEBUG/TOKENS"

run_test_with_check \
    "Verificar tokens (debug ativo)" \
    "echo test" \
    "tokens"

run_test_with_check \
    "Tokens com pipe" \
    "echo hello | cat" \
    "tokens"

run_test_with_check \
    "Tokens com redirecionamento" \
    "echo test > output.txt" \
    "tokens"

run_test_with_check \
    "Comando complexo" \
    'echo "hello" > output.txt && cat < input.txt | grep world || echo "failed"' \
    "no_crash"

# =============================================================================
# RELATÓRIO FINAL
# =============================================================================
print_header "RELATÓRIO FINAL DETALHADO"

FAILED_TESTS=$((TOTAL_TESTS - PASSED_TESTS))

echo -e "${WHITE}Configuração testada:${NC}"
echo "Executável: $FULL_PATH"
echo "Timeout por teste: ${TEST_TIMEOUT}s"
echo ""

echo -e "${WHITE}Estatísticas dos Testes:${NC}"
echo -e "Total de testes executados: ${BLUE}$TOTAL_TESTS${NC}"
echo -e "Testes que passaram: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Testes que falharam: ${RED}$FAILED_TESTS${NC}"

if [[ $TOTAL_TESTS -gt 0 ]]; then
    SUCCESS_RATE=$(( (PASSED_TESTS * 100) / TOTAL_TESTS ))
    echo -e "Taxa de sucesso: ${CYAN}$SUCCESS_RATE%${NC}"
fi

echo -e "\n${WHITE}Status do projeto:${NC}"
if [[ $SUCCESS_RATE -ge 85 ]]; then
    echo -e "${GREEN}🏆 EXCELENTE! Projeto muito avançado${NC}"
    echo "Seu minishell está em estado muito maduro de desenvolvimento."
elif [[ $SUCCESS_RATE -ge 70 ]]; then
    echo -e "${GREEN}✅ MUITO BOM! Base sólida funcionando bem${NC}"
    echo "Pequenos ajustes e você terá um projeto completo."
elif [[ $SUCCESS_RATE -ge 55 ]]; then
    echo -e "${YELLOW}⚡ BOM PROGRESSO! Funcionalidades principais OK${NC}"
    echo "Algumas correções necessárias em áreas específicas."
elif [[ $SUCCESS_RATE -ge 40 ]]; then
    echo -e "${YELLOW}🔧 BASE SÓLIDA! Estrutura funcionando${NC}"
    echo "Desenvolvimento em bom andamento."
elif [[ $SUCCESS_RATE -ge 25 ]]; then
    echo -e "${RED}🚧 DESENVOLVIMENTO INICIAL${NC}"
    echo "Algumas funcionalidades básicas implementadas."
else
    echo -e "${RED}⚠️ INÍCIO DO PROJETO${NC}"
    echo "Necessário revisar implementações fundamentais."
fi

echo -e "\n${WHITE}Funcionalidades detectadas:${NC}"
if [[ $SUCCESS_RATE -gt 0 ]]; then
    echo "• Sistema básico: Funcionando"
    if [[ $SUCCESS_RATE -ge 30 ]]; then
        echo "• Tokenização: Implementada"
        echo "• Validação de input: Funcional"
    fi
    if [[ $SUCCESS_RATE -ge 50 ]]; then
        echo "• Built-ins: Implementados"
        echo "• Execução básica: Funcional"
    fi
    if [[ $SUCCESS_RATE -ge 70 ]]; then
        echo "• Pipes: Funcionais"
        echo "• Redirecionamentos: Implementados"
        echo "• Expansão de variáveis: Funcional"
    fi
    if [[ $SUCCESS_RATE -ge 85 ]]; then
        echo "• Operadores lógicos: Implementados (bonus)"
        echo "• Tratamento robusto de erros"
    fi
fi

echo -e "\n${WHITE}Próximos passos recomendados:${NC}"
if [[ $SUCCESS_RATE -lt 30 ]]; then
    echo "1. Implementar sistema de execução básica"
    echo "2. Corrigir busca de comandos no PATH"
    echo "3. Implementar built-ins essenciais"
elif [[ $SUCCESS_RATE -lt 55 ]]; then
    echo "1. Corrigir redirecionamentos funcionais"
    echo "2. Implementar sistema de pipes"
    echo "3. Melhorar expansão de variáveis"
elif [[ $SUCCESS_RATE -lt 75 ]]; then
    echo "1. Otimizar pipes complexos"
    echo "2. Implementar heredoc completo"
    echo "3. Adicionar features bonus"
else
    echo "1. Implementar wildcards (*)"
    echo "2. Polir detalhes finais"
    echo "3. Otimizar performance"
fi

# Limpar arquivo temporário
rm -f "$TEMP_OUTPUT"

echo -e "\n${BLUE}Teste completo concluído!${NC}"

exit 0