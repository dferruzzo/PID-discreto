import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

# Verificar se um arquivo foi fornecido como argumento
if len(sys.argv) < 2:
    print("Uso: python plots.py resultados.csv")
    sys.exit(1)

# Carregar dados do CSV
filename = sys.argv[1]

# Verificar se o arquivo existe
if not os.path.exists(filename):
    print(f"Erro: Arquivo '{filename}' não encontrado!")
    sys.exit(1)

# Tentar ler o arquivo de diferentes maneiras
try:
    # Primeiro, vamos verificar o conteúdo do arquivo
    with open(filename, 'r') as f:
        linhas = f.readlines()
        print("Primeiras 5 linhas do arquivo:")
        print(''.join(linhas[:5]))
        
        # Mostrar qual linha será ignorada
        print("\nIgnorando a primeira linha:")
        print(linhas[0])
    
    # Tentar ler com pandas, pulando apenas a primeira linha
    data = pd.read_csv(filename, skiprows=1)
    
    # Mostrar as colunas disponíveis
    print("\nColunas disponíveis no CSV após pular 1 linha:")
    print(data.columns.tolist())
    
    # Se chegou até aqui, temos dados, mas talvez com nomes de colunas diferentes
    # Vamos usar os nomes de colunas reais em vez dos esperados
    colunas = data.columns.tolist()
    
    # Criar gráfico
    plt.figure(figsize=(10, 6))
    
    # Usar a primeira coluna como eixo x (geralmente é o tempo)
    x_col = colunas[0]
    
    # Plotar todas as outras colunas
    for i, col in enumerate(colunas[1:], 1):
        style = ['r--', 'b-', 'g-', 'k-.', 'm:', 'c-'][i % 6]
        alpha = 0.7 if i == 3 else 1.0  # Terceira coluna com transparência
        plt.plot(data[x_col], data[col], style, label=col, alpha=alpha)
    
    plt.grid(True)
    plt.xlabel(x_col)
    plt.ylabel('Valores')
    plt.title('Resposta do Sistema com Controlador PID')
    plt.legend()
    
    # Salvar e mostrar
    output_path = 'resposta_pid.png'
    plt.savefig(output_path)
    print(f"\nGráfico salvo em: {os.path.abspath(output_path)}")
    plt.show()
    
except Exception as e:
    print(f"Erro ao processar o arquivo CSV: {e}")
    
    # Tentativa alternativa: sem cabeçalho após pular a primeira linha
    try:
        print("\nTentando ler o arquivo pulando 1 linha e sem cabeçalho...")
        data = pd.read_csv(filename, skiprows=1, header=None, 
                          names=['Tempo', 'Setpoint', 'Saída', 'ControlPID'])
        
        # Criar gráfico
        plt.figure(figsize=(10, 6))
        plt.plot(data['Tempo'], data['Setpoint'], 'r--', label='Setpoint')
        plt.plot(data['Tempo'], data['Saída'], 'b-', label='Saída do Sistema')
        plt.plot(data['Tempo'], data['ControlPID'], 'g-', label='Sinal de Controle', alpha=0.7)
        
        plt.grid(True)
        plt.xlabel('Tempo (s)')
        plt.ylabel('Valores')
        plt.title('Resposta do Sistema com Controlador PID')
        plt.legend()
        
        # Salvar e mostrar
        output_path = 'resposta_pid.png'
        plt.savefig(output_path)
        print(f"\nGráfico salvo em: {os.path.abspath(output_path)}")
        plt.show()
        
    except Exception as e2:
        print(f"Segunda tentativa falhou: {e2}")
        
        # Terceira tentativa: detectar automaticamente o número de linhas a pular
        try:
            print("\nTentando detectar automaticamente cabeçalho...")
            
            # Ler as primeiras linhas para análise
            with open(filename, 'r') as f:
                linhas = f.readlines()
            
            # Encontrar a primeira linha que parece conter dados numéricos
            linhas_a_pular = 0
            for i, linha in enumerate(linhas):
                # Verificar se a linha possui números (usando uma heurística simples)
                if ',' in linha and any(c.isdigit() for c in linha):
                    linhas_a_pular = i
                    break
            
            print(f"Pulando {linhas_a_pular} linhas...")
            
            # Tentar ler novamente com o número correto de linhas a pular
            data = pd.read_csv(filename, skiprows=linhas_a_pular, header=None,
                              names=['Tempo', 'Setpoint', 'Saída', 'ControlPID'])
            
            # Criar gráfico
            plt.figure(figsize=(10, 6))
            plt.plot(data['Tempo'], data['Setpoint'], 'r--', label='Setpoint')
            plt.plot(data['Tempo'], data['Saída'], 'b-', label='Saída do Sistema')
            plt.plot(data['Tempo'], data['ControlPID'], 'g-', label='Sinal de Controle', alpha=0.7)
            
            plt.grid(True)
            plt.xlabel('Tempo (s)')
            plt.ylabel('Valores')
            plt.title('Resposta do Sistema com Controlador PID')
            plt.legend()
            
            # Salvar e mostrar
            output_path = 'resposta_pid.png'
            plt.savefig(output_path)
            print(f"\nGráfico salvo em: {os.path.abspath(output_path)}")
            plt.show()
            
        except Exception as e3:
            print(f"Todas as tentativas falharam!")
            print(f"Erro final: {e3}")
            print("\nDica: Verifique o formato do seu arquivo CSV e forneça manualmente as linhas a pular.")