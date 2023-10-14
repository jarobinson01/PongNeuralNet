#pragma once

#include <vector>

#include "Neuron.h"

class Net {
    std::vector<Layer> m_layers;
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;
public:
    Net(const std::vector<unsigned>&);
    void feedForward(const std::vector<double>&);
    void backProp(const std::vector<double>&);
    void getResults(std::vector<double>&) const;
};