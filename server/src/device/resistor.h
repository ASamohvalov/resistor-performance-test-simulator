#ifndef RESISTOR_H
#define RESISTOR_H

#include <utility>

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
    // @return 0 if error
    double calculateResistanceByTemp(const Resistor& resistor, double temp);
    // @return first - voltage, second - power
    std::pair<double, double> calculateVoltageAndPowerByAmperage(
                const Resistor& resistor, double amperage);
}

#endif