#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{

}

GeneticAlgorithm *GeneticAlgorithm::Make(QJsonObject &paramsObj)
{
    GeneticAlgorithm *instance = new GeneticAlgorithm();
    instance->SetNetworkParams(paramsObj);
    return instance;
}

float GeneticAlgorithm::EvaluateFitness(Chromosome *chromosome)
{
    for(int i = 0; i < chromosome->genes.size(); ++i)
        funcAgs[i] = chromosome->genes[i];
    QScriptValue result = func.call(QScriptValue(), funcAgs);
    float resultValue = result.toVariant().toDouble();
    return 1 / (fabs(resultValue - params.targetResult) + 1);
}

bool GeneticAlgorithm::SetNetworkParams(QJsonObject paramsObj)
{
    params.fitnessThreshold = paramsObj.value("fitnessThreshold").toDouble();
    params.iterations = paramsObj.value("iterations").toInt();
    params.targetResult = paramsObj.value("targetResult").toDouble();
    params.populationSize = paramsObj.value("populationSize").toInt();
    params.geneCapacity = paramsObj.value("geneCapacity").toInt();
}

void GeneticAlgorithm::SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples)
{
    variables.clear();
    QString funcStr = parameters.value("Func").toString();
    QRegExp variablesFinder("[a-z]");
    int pos = 0;
    while (pos >= 0) {
        pos = variablesFinder.indexIn(funcStr, pos);
        if (pos >= 0){
            QString variable = variablesFinder.cap(0);
            if(!variables.contains(variable))
                variables.append(variable);
            ++pos;
        }
    }

    QString variablesStr;
    for(int i = 0; i < variables.size(); ++i)
    {
        if(i) variablesStr.append(", ");
        variablesStr.append(variables[i]);
    }
    qDebug() << variablesStr;

    params.genesCount = variables.size();
    funcStr = QString("(function(%1) { return %2; })").arg(variablesStr).arg(funcStr);
    func = myEngine.evaluate(funcStr);
    funcAgs.clear();
    for(int i = 0; i < params.genesCount; ++i)
        funcAgs.append(0);
}

void GeneticAlgorithm::SetupSamplesI(QJsonObject parameters, QVector<InputSampleI> *samples)
{

}

bool GeneticAlgorithm::AddLayer(QJsonObject layerParams)
{

}

void GeneticAlgorithm::ResetLayers()
{

}

float GeneticAlgorithm::RunTrainSet()
{

}

QVector<QVariant> GeneticAlgorithm::RunTrainingAndGetResult()
{
    if(!params.populationSize) return QVector<QVariant>();

    for(int i = 0; i < params.populationSize; ++i)
    {
        Chromosome *newChromosome = new Chromosome(params.genesCount, params.geneCapacity);
        chromosomes.append(newChromosome);
    }

    float maxFitness = 0;
    float sumFitness = 0;
    float bufFitness = 0;
    int iteration = 0;
    int childsOverIteration = 5;
    int rouletteSpins = 2 * childsOverIteration;
    QVector<Chromosome*> breedChromosomes;
    QMap<float, Chromosome*> tournirTable;
    QVector<Chromosome*>::Iterator chromosomesIter;

    bool firstRun = true;
    do
    {
        // Evaluate fitness
        sumFitness = 0;
        chromosomesIter = chromosomes.begin();
        while(chromosomesIter != chromosomes.end())
        {
            bufFitness = EvaluateFitness((*chromosomesIter));
            sumFitness += bufFitness;
            (*chromosomesIter)->fitness = bufFitness;
            if(maxFitness < bufFitness) maxFitness = bufFitness;
            ++chromosomesIter;
        }
        firstRun = false;
        // Breed - Pairs
        breedChromosomes.clear();
        for(int i = 0; i < rouletteSpins; ++i)
        {
            float rouletteValue = (qrand() % 100) / 100.;
            float rouletteBuf = 0;
            chromosomesIter = chromosomes.begin();
            while(chromosomesIter != chromosomes.end())
            {
                rouletteBuf += (*chromosomesIter)->fitness / sumFitness;
                if(rouletteBuf >= rouletteValue)
                {
                    breedChromosomes.append((*chromosomesIter));
                    break;
                }
                ++chromosomesIter;
            }
        }
        // Breed - Childs
        for(int i = 0; i < childsOverIteration; ++i)
        {
            Chromosome *child = Chromosome::Breed(breedChromosomes[i], breedChromosomes[i+1]);
            chromosomes.append(child);
        }
        // Evaluate fitness
        sumFitness = 0;
        chromosomesIter = chromosomes.begin();
        while(chromosomesIter != chromosomes.end())
        {
            bufFitness = EvaluateFitness((*chromosomesIter));
            sumFitness += bufFitness;
            (*chromosomesIter)->fitness = bufFitness;
            if(maxFitness < bufFitness) maxFitness = bufFitness;
            ++chromosomesIter;
        }
        // Tournir
        for(int i = 0; i < chromosomes.size(); ++i)
            tournirTable.insertMulti(-chromosomes[i]->fitness, chromosomes[i]);
        chromosomes.clear();
        chromosomes = tournirTable.values().toVector();
        tournirTable.clear();
        for(int i = chromosomes.size()-1; i >= params.populationSize; --i)
        {
            delete chromosomes[i];
            chromosomes.removeLast();
        }
        ++iteration;
    }
    while(maxFitness > params.fitnessThreshold && iteration < params.iterations);

    chromosomesIter = chromosomes.begin();
    while(chromosomesIter != chromosomes.end())
    {
        qDebug() << (*chromosomesIter)->fitness;
        qDebug() << (*chromosomesIter)->genes;
        ++chromosomesIter;
    }
}

float GeneticAlgorithm::RunTestSet()
{

}
