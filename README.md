# C++ Codespace Project

Este projeto é uma aplicação C++ que demonstra a estrutura básica de um projeto utilizando CMake, com suporte a testes unitários e um ambiente de desenvolvimento configurado para Codespaces.

## Estrutura do Projeto

```
cpp-codespace-project
├── src
│   ├── main.cpp          # Ponto de entrada da aplicação
│   └── utils
│       ├── helpers.cpp   # Implementação de funções auxiliares
│       └── helpers.h     # Declarações das funções auxiliares
├── include
│   └── project
│       └── common.h      # Definições comuns e declarações
├── tests
│   └── test_main.cpp     # Testes unitários para o projeto
├── CMakeLists.txt        # Script de configuração do CMake
├── .devcontainer
│   ├── devcontainer.json  # Configuração do ambiente de desenvolvimento
│   └── Dockerfile         # Definição da imagem Docker
├── .vscode
│   ├── launch.json        # Configurações de depuração
│   ├── tasks.json         # Definições de tarefas
│   └── settings.json      # Configurações específicas do projeto
├── .gitignore             # Arquivos a serem ignorados pelo controle de versão
└── README.md              # Documentação do projeto
```

## Instalação

1. Clone o repositório:
   ```
   git clone <URL_DO_REPOSITORIO>
   cd cpp-codespace-project
   ```

2. Abra o projeto em um Codespace ou em seu ambiente de desenvolvimento local.

3. Compile o projeto utilizando CMake:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

## Uso

Após a compilação, você pode executar a aplicação gerada:
```
./nome_do_executavel
```

## Testes

Para executar os testes unitários, você pode usar o seguinte comando no diretório `build`:
```
make test
```

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests. Certifique-se de seguir as diretrizes de contribuição.

## Licença

Este projeto está licenciado sob a MIT License. Veja o arquivo LICENSE para mais detalhes.