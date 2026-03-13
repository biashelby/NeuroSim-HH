import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('dados_neuronio.csv')

    # Criando a figura e definindo o fundo preto ANTES de qualquer coisa
    fig = plt.figure(figsize=(12, 6), facecolor='black')
    ax = fig.add_subplot(111)
    ax.set_facecolor('black')

    # Plotando com cores neon para contraste máximo
    ax.plot(df['Tempo'], df['Voltagem'], color='#00FF00', linewidth=2, label='Potencial de Membrana')
    ax.axhline(y=-55, color='red', linestyle='--', label='Limiar')

    # Forçando todas as cores para branco/cinza claro
    ax.spines['bottom'].set_color('white')
    ax.spines['top'].set_color('white') 
    ax.spines['right'].set_color('white')
    ax.spines['left'].set_color('white')
    ax.tick_params(axis='x', colors='white')
    ax.tick_params(axis='y', colors='white')
    ax.yaxis.label.set_color('white')
    ax.xaxis.label.set_color('white')
    ax.title.set_color('white')

    plt.title('Simulacao Hodgkin-Huxley | Neurotech Protocol', pad=20)
    plt.xlabel('Tempo (ms)')
    plt.ylabel('Voltagem (mV)')
    plt.legend(facecolor='black', edgecolor='white')

    # SALVANDO O ARQUIVO (A prova real)
    plt.savefig('spike_neural_dark.png', facecolor=fig.get_facecolor(), edgecolor='none')
    
    print("Arquivo 'spike_neural_dark.png' gerado com sucesso!")
    plt.show()

except Exception as e:
    print(f"Erro: {e}")