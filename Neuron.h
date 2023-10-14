#pragma once

#include <vector>
#include <cstdlib>

#include "Connection.h"

class Neuron;
typedef std::vector<Neuron> Layer;

class Neuron {
    static double transferFunction(double);
    static double transferFunctionDerivative(double);
    static double randomWeight() { return rand() / double(RAND_MAX); }
    double sumDOW(const Layer&) const;
    double m_outputVal;
    std::vector<Connection> m_outputWeights;
    unsigned m_myIndex;
    double m_gradient;
    static double eta;      // [0.0...1.0] overall net training rate
    static double alpha;    // [0.0...n] multiplier of last weight change (momentum)
public:
    Neuron(unsigned, unsigned);
    double getOutputVal() const { return m_outputVal; }
    void setOutputVal(double val) { m_outputVal = val; }
    void feedForward(const Layer&);
    void calcOutputGradients(double);
    void calcHiddenGradients(const Layer&);
    void updateInputWeights(Layer&);
};
