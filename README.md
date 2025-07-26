# 🐚 Minishell
### As Beautiful as a Shell

Este é o projeto **Minishell** da 42, implementando um shell funcional em C.

## 🚀 Como Compilar

```bash
# Clonar com submodules
git clone --recurse-submodules [seu-repo]

# Compilar
make

# Executar
./minishell
```

## 📁 Estrutura do Projeto

```
minishell/
├── libft/              # Submodule da libft
├── includes/           # Headers do projeto
│   ├── minishell.h     # Header principal
│   ├── structs.h       # Estruturas de dados
│   ├── colors.h        # Sistema de cores
│   └── terminal.h      # Terminal
├── srcs/               # Código fonte
│   ├── main.c          # Função main
│   ├── check_args.c    # Validação de argumentos
│   └── terminal/       # Sistema de terminal
└── Makefile           # Build system
```

## 🎯 Status de Desenvolvimento

### ✅ Dia 01 - Setup e Arquitetura (Completo)
- [x] Setup inicial com submodule
- [x] Makefile completo
- [x] Estrutura de diretórios
- [x] Headers fundamentais
- [x] Sistema de argumentos e main
- [x] Terminal básico funcionando

### 📋 Próximos Passos
- [ ] Validação de input completa
- [ ] Sistema de sinais
- [ ] Tokenização
- [ ] Built-ins
- [ ] Execução de comandos

## 📝 Funcionalidades Implementadas

- ✅ Prompt interativo colorido
- ✅ Histórico de comandos
- ✅ Exit com Ctrl+D ou comando "exit"
- ✅ Estrutura modular e organizada

## 👥 Autores

- **[Seu Nome]** - Desenvolvimento principal
- Baseado no projeto de referência de [@marsoare](https://github.com/MarkosComK) e [@hluiz-ma](https://github.com/SirAlabar)

## 🔧 Comandos Make

```bash
make            # Compila o projeto
make clean      # Remove objetos
make fclean     # Remove tudo
make re         # Recompila tudo
make test       # Testa com valgrind
```

## 📚 Recursos Utilizados

- **Readline**: Para input interativo e histórico
- **Libft**: Biblioteca de funções customizada
- **POSIX**: Padrões Unix para compatibilidade

