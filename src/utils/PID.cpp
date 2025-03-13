#include "project/PID.h"
#include <algorithm>  // Para std::clamp

// Construtor
PID::PID(double kp, double ki, double kd, double sampleTimeS, double outMin, double outMax) 
    : kp(kp), ki(ki), kd(kd), outMin(outMin), outMax(outMax), sampleTimeS(sampleTimeS) {
    reset();
}

// Resetar o controlador
void PID::reset() {
    integralSum = 0.0;
    lastError = 0.0;
    lastMeasurement = 0.0;
    firstRun = true;
}

// Configurar parâmetros do PID
void PID::setTunings(double _kp, double _ki, double _kd) {
    if (_kp < 0 || _ki < 0 || _kd < 0) return;
    
    kp = _kp;
    // Ajustando ki e kd ao período de amostragem
    ki = _ki * sampleTimeS;
    kd = _kd / sampleTimeS;
}

void PID::setSampleTime(double _sampleTimeS) {
    if (_sampleTimeS <= 0) return;
    
    // Ajustar ki e kd se o tempo de amostragem mudar
    double ratio = _sampleTimeS / sampleTimeS;
    ki *= ratio;
    kd /= ratio;
    
    sampleTimeS = _sampleTimeS;
}

void PID::setOutputLimits(double min, double max) {
    if (min >= max) return;
    
    outMin = min;
    outMax = max;
    
    // Se o integralSum atual estiver fora dos novos limites, corrija
    integralSum = std::clamp(integralSum, outMin, outMax);
}

void PID::setSetpoint(double _setpoint) {
    setpoint = _setpoint;
}

// Método principal para computar a saída do controlador
double PID::compute(double measurement) {
    // Calcular erro
    double error = setpoint - measurement;
    
    // Termo proporcional
    double pTerm = kp * error;
    
    // Termo integral (soma acumulada)
    integralSum += ki * error;
    // Anti-windup: limitar o termo integral
    integralSum = std::clamp(integralSum, outMin, outMax);
    double iTerm = integralSum;
    
    // Termo derivativo (baseado na variação da medição para reduzir kicks)
    double dTerm = 0;
    if (!firstRun) {
        dTerm = -kd * (measurement - lastMeasurement);
    }
    
    // Saída total
    double output = pTerm + iTerm + dTerm;
    
    // Limitar a saída
    output = std::clamp(output, outMin, outMax);
    
    // Atualizar variáveis para próxima iteração
    lastError = error;
    lastMeasurement = measurement;
    firstRun = false;
    
    return output;
}