#ifndef PARAMETERS_H
#define PARAMETERS_H
namespace Perceptron {
    struct NetworkParams{
        int maxEpoch;
        float trainErrorThreshold;
        float testErrorThreshold;
        float minWeight;
        float maxWeight;
    };

    struct LayerParams{
        int size;
        float LearnSpeed;
        float Moment;
        float FuncIndent;
        float Bias;
    };

    enum LayerType{
        Input,
        Hidden,
        Output
    };
}

namespace ART {
    struct NetworkParams{
        int size;
        float similarity;
        float L;
    };
}

namespace GeneticAlgorithmParams {
    struct Parameters{
        float fitnessThreshold;
        int iterations;
        float targetResult;

        int populationSize;
        int genesCount;
        int geneCapacity;
    };
}

#endif // PARAMETERS_H
