# Projeto WAR Estruturado – Níveis Novato, Aventureiro e Mestre

Este repositório contém minha evolução no desenvolvimento do sistema **WAR Estruturado**, seguindo as etapas propostas no PDF: **Nível Novato**, **Nível Aventureiro** e **Nível Mestre**.  
Cada etapa adiciona novas funcionalidades, técnicas de programação e boas práticas.

---

# Nível Novato – Construção dos Territórios
No primeiro nível, o objetivo foi montar a base do sistema:

- Criação da struct `Territorio`
- Cadastro de 5 territórios
- Armazenamento de nome, cor e tropas
- Exibição dos territórios cadastrados
- Uso de vetor de structs
- Entrada simples com `scanf`
- Código ainda básico, pensando como iniciante

Arquivo: **war_novato.c**

---

## Nível Aventureiro – Sistema de Ataques
No nível intermediário, o sistema evoluiu para permitir batalhas entre territórios:

- Uso de **malloc** para alocar territórios dinamicamente
- Jogador escolhe atacante e defensor
- Função `atacar()` usando rolagem de dados (rand)
- Atualização de cor e tropas após o combate
- Validação para impedir atacar territórios da mesma cor
- Funções separadas para cadastro, exibição, ataque e liberação
- Uso de ponteiros para manipular os territórios
- Uso de `free()` ao final

Arquivo: **war_aventureiro.c**

---

# Nível Mestre – Missões Estratégicas
No último nível, o jogo recebeu uma camada estratégica mais complexa:

- Vetor de missões pré-definidas
- Missão sorteada automaticamente para cada jogador
- Missões armazenadas dinamicamente com `malloc`
- Função `atribuirMissao()` usando `strcpy`
- Verificação automática das missões a cada turno
- Jogadores definidos dinamicamente (quantidade escolhida pelo usuário)
- Integração com sistema de ataques e mapa do nível anterior
- Função `verificarMissao()` com lógica simples de cumprimento
- Função `liberarMemoria()` para limpar tudo no final

Arquivo: **war_mestre.c**

---

## Como Compilar e Rodar
No terminal ou VS Code:
gcc nome_do_arquivo.c -o jogo
./jogo


## Estrutura do Repositório

/inventario_desafio
- war_novato.c
- war_aventureiro.c
- war_mestre.c
- README.md
