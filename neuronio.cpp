#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

/**
 * PROJETO: Hodgkin-Huxley Deep Neuron Simulator
 * NÍVEL: Pesquisa Avançada / Bioengenharia
 */

struct NeuronState {
    double V; // Potencial de membrana
    double m; // Ativação de Sódio
    double h; // Inativação de Sódio
    double n; // Ativação de Potássio
};

class HodgkinHuxley {
private:
    // Constantes Biofísicas Reais
    const double C_m = 1.0;    // Capacitância (uF/cm^2)
    const double g_Na = 120.0; // Condutância Sódio
    const double g_K = 36.0;   // Condutância Potássio
    const double g_L = 0.3;    // Condutância de Vazamento
    const double E_Na = 50.0;  // Potencial de reversão Na (mV)
    const double E_K = -77.0;  // Potencial de reversão K (mV)
    const double E_L = -54.387;// Potencial de reversão Leak (mV)

    // Funções de Transição (Taxas de abertura/fechamento de canais iônicos)
    double alpha_m(double V) { return 0.1 * (25.0 - V) / (exp((25.0 - V) / 10.0) - 1.0); }
    double beta_m(double V)  { return 4.0 * exp(-V / 18.0); }
    double alpha_h(double V) { return 0.07 * exp(-V / 20.0); }
    double beta_h(double V)  { return 1.0 / (exp((30.0 - V) / 10.0) + 1.0); }
    double alpha_n(double V) { return 0.01 * (10.0 - V) / (exp((10.0 - V) / 10.0) - 1.0); }
    double beta_n(double V)  { return 0.125 * exp(-V / 80.0); }

public:
    // A função solve agora recebe o arquivo para gravar os dados diretamente
    void solve(std::ofstream& arquivo) {
        double dt = 0.01; // Passo de tempo (ms)
        double T = 50.0;  // Tempo total (ms)
        NeuronState s = {-65.0, 0.05, 0.6, 0.32}; // Estado inicial de repouso
        double I_ext = 10.0; // Corrente injetada (o estímulo)

        for (double t = 0; t < T; t += dt) {
            // Cálculo das correntes iônicas baseadas no modelo
            double I_Na = g_Na * pow(s.m, 3) * s.h * (s.V - E_Na);
            double I_K  = g_K * pow(s.n, 4) * (s.V - E_K);
            double I_L  = g_L * (s.V - E_L);

            // Método de Euler para resolver as Equações Diferenciais
            s.V += (dt / C_m) * (I_ext - (I_Na + I_K + I_L));
            s.m += dt * (alpha_m(s.V) * (1.0 - s.m) - beta_m(s.V) * s.m);
            s.h += dt * (alpha_h(s.V) * (1.0 - s.h) - beta_h(s.V) * s.h);
            s.n += dt * (alpha_n(s.V) * (1.0 - s.n) - beta_n(s.V) * s.n);

            // Salva no arquivo no formato CSV: Tempo,Voltagem
            arquivo << t << "," << s.V << "\n";
        }
    }
};

int main() {
    // 1. Abrimos o arquivo onde os dados serão armazenados
    std::ofstream arquivo("dados_neuronio.csv");
    
    // 2. Escrevemos o cabeçalho do CSV
    arquivo << "Tempo,Voltagem\n"; 

    // 3. Criamos a instância do simulador e rodamos
    HodgkinHuxley neuron;
    
    std::cout << "--- INICIANDO SIMULACAO BIOFISICA ---" << std::endl;
    neuron.solve(arquivo); 
    
    // 4. Fechamos o arquivo e encerramos
    arquivo.close();

    std::cout << "Status: Concluido com sucesso." << std::endl;
    std::cout << "Arquivo gerado: dados_neuronio.csv" << std::endl;
    std::cout << "Pronta para a visualização em Python, Dra. Shelby." << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    return 0;
}