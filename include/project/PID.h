#ifndef PID_H
#define PID_H

class PID {
private:
    // Parâmetros do controlador
    double kp;    // Ganho proporcional
    double ki;    // Ganho integral
    double kd;    // Ganho derivativo
    
    // Variáveis internas
    double setpoint;      // Valor desejado
    double integralSum;   // Soma para termo integral
    double lastError;     // Erro anterior para termo derivativo
    double lastMeasurement; // Medição anterior
    double outMin;        // Limite mínimo de saída
    double outMax;        // Limite máximo de saída
    double sampleTimeS;   // Tempo de amostragem em segundos
    
    // Flags
    bool firstRun;        // Indica primeira execução
    
public:
    // Construtor
    PID(double kp, double ki, double kd, double sampleTimeS, double outMin, double outMax);
    
    // Inicialização
    void reset();
    
    // Configurar parâmetros
    void setTunings(double kp, double ki, double kd);
    void setSampleTime(double sampleTimeS);
    void setOutputLimits(double min, double max);
    void setSetpoint(double setpoint);
    
    // Computar saída do controlador
    double compute(double measurement);
    
    // Getters
    double getKp() const { return kp; }
    double getKi() const { return ki; }
    double getKd() const { return kd; }
    double getSetpoint() const { return setpoint; }
};

#endif // PID_H