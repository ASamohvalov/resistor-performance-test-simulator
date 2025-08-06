#ifndef RESISTOR_H
#define RESISTOR_H

namespace device
{
    struct Resistor
    {
        double resistance; // сопротивление
        const double resistance_coefficient = 0.0039; // коэффициент сопротивления, медь по дефолту
    };

    extern const Resistor baseResistor;
    Resistor getCurrentResistor();

    // for metallic resistors
    double calculateResistanceByTemp(const Resistor& resistor, double temp);
    double calculateVoltageByAmperage(const Resistor& resistor, double amperage);
}

#endif