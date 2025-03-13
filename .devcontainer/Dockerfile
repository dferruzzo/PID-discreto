FROM ubuntu:22.04

# Evitar interações durante a instalação de pacotes
ARG DEBIAN_FRONTEND=noninteractive

# Instalar dependências essenciais de sistema e desenvolvimento
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    curl \
    wget \
    pkg-config \
    zip \
    unzip \
    python3 \
    python3-pip \
    python3-dev \
    python3-setuptools \
    python3-matplotlib \
    python3-pandas \
    sudo \
    locales \
    && rm -rf /var/lib/apt/lists/*

# Configurar localização
RUN locale-gen en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8

# Criar usuário não-root com mesmo UID/GID que o VSCode usa
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Configurar matplotlib para trabalhar sem exibição gráfica
RUN mkdir -p /home/$USERNAME/.config/matplotlib && \
    echo "backend : Agg" > /home/$USERNAME/.config/matplotlib/matplotlibrc && \
    chown -R $USERNAME:$USERNAME /home/$USERNAME/.config

# Ferramentas adicionais úteis para desenvolvimento
RUN apt-get update && apt-get install -y \
    valgrind \
    ccache \
    ninja-build \
    clang \
    clang-format \
    clang-tidy \
    && rm -rf /var/lib/apt/lists/*

# Adicionar suporte a Jupyter Notebook
RUN pip3 install --no-cache-dir \
    jupyter \
    notebook \
    jupyterlab

# Criar diretório de trabalho
WORKDIR /workspaces/pid-discreto

# Definir o usuário padrão
USER $USERNAME

# Não definir comando padrão para permitir que o devcontainer.json controle isso
CMD ["/bin/bash"]