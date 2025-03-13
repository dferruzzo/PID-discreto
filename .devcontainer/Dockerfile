FROM ubuntu:20.04

# Instala dependências necessárias
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Define o diretório de trabalho
WORKDIR /workspace

# Copia os arquivos do projeto para o contêiner
COPY . .

# Comando padrão para compilar o projeto
CMD ["cmake", ".", "&&", "make"]