#include <iostream>
#include <vector>
//#include "project/common.h"
//#include "utils/helpers.h"
#include "project/PID.h"

// Função para simular um sistema de primeira ordem
double simulateSystem(double input, double& lastOutput, double timeConstant, double gain, double sampleTime) {
    // Modelo discreto simplificado: y[k+1] = a*y[k] + b*u[k]
    double a = exp(-sampleTime / timeConstant);
    double b = gain * (1 - a);
    
    double output = a * lastOutput + b * input;
    lastOutput = output;
    return output;
}

int main() {
    std::cout << "Demonstração de Controlador PID Discreto" << std::endl;

    // Parâmetros do PID
    double kp = 2.0;    // Ganho proporcional
    double ki = 0.5;    // Ganho integral
    double kd = 0.1;    // Ganho derivativo
    double sampleTime = 0.001;  // 10ms
    
    // Criar controlador PID
    PID pid(kp, ki, kd, sampleTime, -100.0, 100.0);
    pid.setSetpoint(50.0);  // Definir setpoint em 50
    
    // Parâmetros do sistema simulado
    double timeConstant = 0.5;  // Constante de tempo
    double gain = 1.0;          // Ganho do sistema
    double systemOutput = 0.0;  // Estado inicial
    
    // Executar simulação por 5 segundos
    const int steps = 5000;  // 5 segundos com sampleTime = 0.01s
    
    std::cout << "Tempo,Setpoint,Saída,ControlPID" << std::endl;
    
    for (int i = 0; i < steps; i++) {
        // Calcular ação de controle
        double controlSignal = pid.compute(systemOutput);
        
        // Aplicar ao sistema
        systemOutput = simulateSystem(controlSignal, systemOutput, timeConstant, gain, sampleTime);
        
        // Mostrar resultados a cada 10 passos
        if (i % 10 == 0) {
            double time = i * sampleTime;
            std::cout << time << "," << pid.getSetpoint() << "," 
                      << systemOutput << "," << controlSignal << std::endl;
        }
    }

    return 0;
}