#include <cassert>
#include <cmath>
#include <iostream>

#include "Net.h"

Net::Net(const std::vector<unsigned>& topology) {
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum < numLayers; layerNum++) {
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum ));
        }
    }

    // Bias node
    m_layers.back().back().setOutputVal(1);
}

void Net::feedForward(const std::vector<double>& inputVals) {
    assert(inputVals.size() == m_layers[0].size() - 1);

    for(unsigned i = 0; i < inputVals.size(); i++) {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    // Forward propogate
    for(unsigned layerNum = 1; layerNum < m_layers.size(); layerNum++) {
        Layer& prevLayer = m_layers[layerNum - 1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; n++) {
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}

void Net::backProp(const std::vector<double>& targetVals) {
    // Calculate net error (RMS)
    Layer& outputLayer = m_layers.back();
    m_error = 0.0;

    for(unsigned n = 0; n < outputLayer.size() -1; n++) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1;
    m_error = sqrt(m_error);

    m_recentAverageError = 
        (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
        / (m_recentAverageSmoothingFactor + 1.0);

    // Calculate output layer gradients
    for(unsigned n = 0; n < outputLayer.size() - 1; n++) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients
    for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; layerNum--) {
        Layer& hiddenLayer = m_layers[layerNum];
        Layer& nextLayer = m_layers[layerNum + 1];

        for(unsigned n = 0; n < hiddenLayer.size(); n++) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // Ca
    for(unsigned layerNum = m_layers.size() - 1; layerNum > 0; layerNum--) {
        Layer& layer = m_layers[layerNum];
        Layer& prevLayer = m_layers[layerNum - 1];

        for(unsigned n = 0; n < layer.size() - 1; n++) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::getResults(std::vector<double>& resultVals) const {
    resultVals.clear();

    for(unsigned n = 0; n < m_layers.back().size() - 1; n++) {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}