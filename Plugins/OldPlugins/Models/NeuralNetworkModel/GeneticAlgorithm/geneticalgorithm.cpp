#include "geneticalgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
    myEngine = NULL;
    params.minRange = std::numeric_limits<float>::min();
    params.maxRange = std::numeric_limits<float>::max();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    for(int i = 0; i < chromosomes.size(); ++i)
        delete chromosomes[i];
    chromosomes.clear();
    if(myEngine) delete myEngine;
}

GeneticAlgorithm *GeneticAlgorithm::Make(QJsonObject &paramsObj)
{
    GeneticAlgorithm *instance = new GeneticAlgorithm();
    instance->SetNetworkParams(paramsObj);
    return instance;
}

float GeneticAlgorithm::EvaluateFitness(Chromosome *chromosome)
{
    //float sumValues = 0;
    for(int i = 0; i < chromosome->genes.size(); ++i)
    {
        funcAgs[i] = chromosome->genes[i];
        //sumValues += fabs(chromosome->genes[i]);
    }
    QScriptValue result = func.call(QScriptValue(), funcAgs);
    float resultValue = result.toVariant().toDouble();
    if(params.extremumSearch != Parameters::None)
    {
        if(params.extremumSearch == Parameters::Min)
            return 1 / (fabs(resultValue) + 1);
        else
            return fabs(resultValue);
    }
    else
    {
        return 1 / (fabs(resultValue - params.targetResult) + 1);
    }
}

bool GeneticAlgorithm::SetNetworkParams(QJsonObject paramsObj)
{
    params.fitnessThreshold = paramsObj.value("fitnessThreshold").toDouble();
    params.iterations = paramsObj.value("iterations").toInt();
    params.targetResult = paramsObj.value("targetResult").toDouble();
    QString typeStr = paramsObj.value("extremumSearch").toString();
    if(!typeStr.compare("min", Qt::CaseInsensitive))
        params.extremumSearch = Parameters::Min;
    else if(!typeStr.compare("max", Qt::CaseInsensitive))
        params.extremumSearch = Parameters::Max;
    else
        params.extremumSearch = Parameters::None;
    params.populationSize = paramsObj.value("populationSize").toInt();
    params.geneCapacity = paramsObj.value("geneCapacity").toInt();

    if(paramsObj.contains("minRange"))
        params.minRange = paramsObj.value("minRange").toDouble();
    if(paramsObj.contains("maxRange"))
        params.maxRange = paramsObj.value("maxRange").toDouble();
}

void GeneticAlgorithm::SetupSamplesF(QJsonObject parameters, QVector<InputSampleF> *samples)
{
    variables.clear();
    QString funcStr = parameters.value("Func").toString();
    QRegExp variablesFinder("[a-z]{1}\\s");
    variablesFinder.setMinimal(true);
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
    if(!myEngine) myEngine = new QScriptEngine();
    func = myEngine->evaluate(funcStr);
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

    if(chromosomes.size() != 0)
    {
        for(int i = 0; i < chromosomes.size(); ++i)
            delete chromosomes[i];
        chromosomes.clear();
    }

    for(int i = 0; i < params.populationSize; ++i)
    {
        Chromosome *newChromosome = new Chromosome(&params);
        chromosomes.append(newChromosome);
    }

    float sumFitness = 0;
    float bufFitness = 0;
    int iteration = 0;
    int childsOverIteration = 5;
    int rouletteSpins = 2 * childsOverIteration;

    QVector<Chromosome*>::Iterator chromosomesIter;
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
        qDebug() << endl << "Iteration" << iteration;
        chromosomesIter = chromosomes.begin();
        while(chromosomesIter != chromosomes.end())
        {
            qDebug() << (*chromosomesIter)->fitness << "->" << (*chromosomesIter)->genes;
            ++chromosomesIter;
        }
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
//        qDebug() << "Breed pairs";
//        chromosomesIter = breedChromosomes.begin();
//        while(chromosomesIter != breedChromosomes.end())
//        {
//            qDebug() << (*chromosomesIter)->fitness;
//            qDebug() << (*chromosomesIter)->genes;
//            ++chromosomesIter;
//        }
        // Breed - Childs
        for(int i = 0; i < childsOverIteration; ++i)
        {
            Chromosome *child = Chromosome::Breed(breedChromosomes[i], breedChromosomes[i+1]);
            chromosomes.append(child);
        }
//        qDebug() << "With childs";
//        chromosomesIter = chromosomes.begin();
//        while(chromosomesIter != chromosomes.end())
//        {
//            qDebug() << (*chromosomesIter)->fitness;
//            qDebug() << (*chromosomesIter)->genes;
//            ++chromosomesIter;
//        }
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
        qDebug() << (*chromosomesIter)->fitness << "->" << (*chromosomesIter)->genes;
        ++chromosomesIter;
    }

    QVector<QVariant> result;
    for(int i = 0; i < chromosomes.first()->genes.size(); ++i)
        result.append(QVariant(chromosomes.first()->genes[i]));
    return result;
}

float GeneticAlgorithm::RunTestSet()
{

}
