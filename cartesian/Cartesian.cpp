#include <deque>
#include "Cartesian.h"
#include "../utility/utilityrng.h"
namespace cartesian{

Cartesian::Cartesian()
{
    name_ = "Cartesian";
}


Cartesian* Cartesian::copy()
{
    auto *newObject = new Cartesian(*this);

    // no deep copy code needed

    return newObject;

}
std::vector<CrossoverOpP> Cartesian::getCrossoverOp()
{
    std::vector<CrossoverOpP> crossoverOperators;
    crossoverOperators.emplace_back((CrossoverOpP) (new CartesianCrxUniform));
    crossoverOperators.emplace_back((CrossoverOpP) (new CartesianCrxHalfUniform));
    crossoverOperators.emplace_back((CrossoverOpP) (new CartesianCrxOnePoint));
    return crossoverOperators;
}

std::vector<MutationOpP> Cartesian::getMutationOp()
{
    std::vector<MutationOpP> mutationOperators;
    mutationOperators.emplace_back((MutationOpP) (new MutateFunction));
    mutationOperators.emplace_back((MutationOpP) (new MutateFunctionSilent));
    mutationOperators.emplace_back((MutationOpP) (new MutateFunctionSwap));
    mutationOperators.emplace_back((MutationOpP) (new MutateConnection));
    mutationOperators.emplace_back((MutationOpP) (new MutateConnectionSilent));
    mutationOperators.emplace_back((MutationOpP) (new MutateIntoSilent));
    return mutationOperators;
}

void Cartesian::registerParameters(StateP state)
{
    registerParameter(state, "numoutputs", (voidP) (new uint(1)), ECF::UINT, "number of functional outputs (default: 1)");
    registerParameter(state, "numrows", (voidP) (new uint(1)), ECF::UINT, "number of rows (default: 1)");
    registerParameter(state, "numcols", (voidP) (new uint(100)), ECF::UINT, "number of columns (default: 100)");
    registerParameter(state, "levelsback", (voidP) (new uint(1)), ECF::UINT, "number of previous columns to be used as possible inputs (default: 1)");
    registerParameter(state, "numvariables", (voidP) (new uint(1)), ECF::UINT, "number of input variables (default: 1)");
    registerParameter(state, "constantset", (voidP) (new std::string), ECF::STRING, "set of functions to use (default: none)");
    registerParameter(state, "functionset", (voidP) (new std::string), ECF::STRING, "set of input constants (default: none)");
}


bool Cartesian::initialize(StateP state)
{
    state_ = state;
    std::stringstream ss;
    std::string names,name;
    voidP sptr;

    // create and initialize the function set
    functionSet_ = static_cast<FunctionSetP> (new FunctionSet);
    functionSet_->initialize(state_);


    uint number;
    //Simple parameters
    sptr = getParameterValue(state, "numvariables");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        std::cerr << "Genotype initialization error: Number of variables is lesser than 1 or can not be parsed into a number.\n";
        return false;
    }
    nVariables = number;

    sptr = getParameterValue(state,"numoutputs");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        std::cerr << "Genotype initialization error: Number of outputs is lesser than 1 or can not be parsed into a number.\n";
        return false;
    }
    nOutputs = number;

    sptr = getParameterValue(state,"numrows");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        std::cerr << "Genotype initialization error: Number of rows is lesser than 1 or can not be parsed into a number.\n";
        return false;
    }
    nRows = number;

    sptr = getParameterValue(state,"numcols");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        std::cerr << "Genotype initialization error: Number of columns is lesser than 1 or can not be parsed into a number.\n";
        return false;
    }
    nCols = number;

    sptr = getParameterValue(state,"levelsback");
    number = *((uint*) sptr.get());
    if(number <= 0) {
        std::cerr << "Genotype initialization error: Number of columns is lesser than 1 or can not be parsed into a number.\n";
        return false;
    }
    nLevelsBack = number;
    if(nLevelsBack > nRows) {
        nLevelsBack = nRows;
    }

    sptr = getParameterValue(state,"constantset");
    names = *((std::string*) sptr.get());
    number = 0;
    ss.str("");
    ss.clear();
    ss << names;
    while(ss >> name) {
        ++number;
        constantSet.push_back(std::stod(name));
    }
    nConstants = number;
    nInputs = nConstants + nVariables;

    //Functionset parametri su malo složeniji
    sptr = getParameterValue(state, "functionset");
    names = *((std::string*) sptr.get());
    ss.str("");
    ss.clear();
    ss << names;
    name="";

    while(ss >> name) {
        functionSet_->addFunction(name);
        nFunctions++;
    }

    std::map<std::string, FunctionP_basic>::iterator it;
    for (it = functionSet_->mActiveFunctions_.begin(); it != functionSet_->mActiveFunctions_.end(); it++) {
        uint nArgs = it->second->getNumOfArgs();
        if (nArgs > maxArity)
        {
            maxArity = nArgs;
        }
    }
    buildRandomGenome();
    return true;
}

void Cartesian::read(XMLNode &xCart)
{
    std::string s = xCart.getText(0);
    std::istringstream ss(s);
    std::string token;
    uint i = 0;
    bool flag = false;
    uint functionId = 0;
    std::vector<uint> operands;
    uint counter = 0;
    while (getline(ss, token, ' '))
    {
        if(!flag) {
            functionId = stoi(token);
            flag = true;
            counter = functionSet_->vActiveFunctions_[functionId]->getNumOfArgs();
        }
        else{
            operands.push_back(stoi(token));
            counter--;
            if(counter == 0) {
                flag = false;
                this->at(i++) = CartesianGene{functionId,operands};
            }
        }
    }
    for(uint j = this->size() - 1; j > this->size() - 1 - nOutputs; j--) {
        this->operator[](j).isOutput = true;
    }
}

void Cartesian::write(XMLNode &xCart)
{
    xCart = XMLNode::createXMLTopNode("Cartesian");
    std::stringstream sValue;
    sValue << this->size();
    xCart.addAttribute("size", sValue.str().c_str());

    sValue.str("");

    // write genome to sValue
    std::vector<CartesianGene>& genome = *this;
    for(const auto& gene : genome)
        sValue << gene;

    xCart.addText(sValue.str().c_str());
}

uint Cartesian::getGenomeSize()
{
    return this->size();
}

uint Cartesian::getRowNumber(uint index)
{
    return index/nCols;
}

/**
 * CGP layout: On top is 1st row, on bottom is nth row.
 * Depending on which row we wish to connect we need its number to check valid connections(only rows
 * before it, depending on levelsback).
 *
 * ROWS AND COLUMNS ARE 0 indexed!!!
 *
 * */
uint Cartesian::randomConnectionGenerator(uint rowNumber)
{
    uint minimum = nInputs + nCols * nLevelsBack;

    //Index of the first element of a row
    uint firstElementOfARow = nInputs + rowNumber*nCols;
    if(minimum <= firstElementOfARow) {
        minimum = firstElementOfARow - nLevelsBack*nCols;
    }
    else {
        minimum = 0;
    }
    return utility::RandomGenerator::get_unifrom_random_uint(minimum, firstElementOfARow - 1);
}

uint Cartesian::randomOutput()
{
    uint minimum = nInputs + (nRows - 1) * nCols;
    uint maximum = nInputs + nRows * nCols;
    return utility::RandomGenerator::get_unifrom_random_uint(minimum, maximum - 1);
}


std::set<uint> Cartesian::allPossibleConnection(uint rowNumber)
{
    uint minimum = nInputs + nCols * (nLevelsBack+1);
    //Index of the first element of a row
    uint firstElementOfARow = nInputs + rowNumber*nCols;
    if(minimum <= firstElementOfARow) {
        minimum = firstElementOfARow - (nLevelsBack*nCols+1);
    }
    else {
        minimum = 0;
    }
    std::set<uint> all;
    for(uint i = minimum; i < firstElementOfARow; i++) {
        all.insert(i);
    }
    return all;
}

/**
 * output_number is 0 indexed.
 * Returned vector contains indexes of Cartesian object. All CartesianGenes
 * contribute in calculation of an output numbered output_number.
 * */
std::vector<uint> Cartesian::getActiveTrail(uint output_number)
{
//    for(uint i = 0; i < this->size(); i++) {
//        std::cout << this->operator[](i) << ' ';
//    }
    std::vector<uint> trail;
    std::deque<uint> working_deque;
    uint start_index = this->size() - nOutputs + output_number;
    uint start_value = this->operator[](start_index).value;
    working_deque.push_back(start_value);
//    std::cout << "start_index: " << start_index << " " << start_value << '\n';
//    std::cout << "nInputs: " << nInputs << '\n';
    while(!working_deque.empty()) {
        uint working_index = working_deque.front();
//        std::cout << "wotking index: " << working_index << '\n';
        working_deque.pop_front();
        if(working_index >= nInputs) {
            trail.push_back(working_index - nInputs);
//            std::cout << "U trail stavio: " << (working_index - nInputs) << '\n';
            const auto& gene = this->at(working_index - nInputs);
            if(gene.isOutput) {
                std::cout << "Something went wrong. Trail is considering an output index.\n";
            }
            for(const auto& elem : gene.inputConnections) {
//                std::cout << "\t\tPlacing element: " << elem << '\n';
                working_deque.push_back(elem);
            }
        }
    }
    return trail;
}

std::vector<std::vector<uint> > Cartesian::getActiveTrails()
{
    std::vector<std::vector<uint>> allTrails;
    for(uint i = 0; i < nOutputs; i++) {
        allTrails.emplace_back(getActiveTrail(i));
    }
    return allTrails;
}


void Cartesian::buildRandomGenome()
{
    std::uniform_int_distribution<uint> distribution(0, functionSet_->vActiveFunctions_.size() - 1);
    using rng = utility::RandomGenerator;
    const auto& vRef = functionSet_->vActiveFunctions_;
    for(uint i = 0; i < nRows; i++) {
        for(uint j = 0; j < nCols; j++) {
            uint functionID = rng::get_unifrom_random_uint(distribution);
            uint noOfOperands = vRef[functionID]->getNumOfArgs();
            std::vector<uint> connections;
            for(uint k = 0; k < noOfOperands; k++) {
                connections.emplace_back(randomConnectionGenerator(i));
            }
            this->emplace_back(CartesianGene{functionID,connections});
        }
    }
    for(uint i = 0; i < nOutputs; i++) {
        this->emplace_back(CartesianGene{randomOutput(), std::vector<uint>{},true});
    }
}

std::string Cartesian::toStringActiveNodes(uint output_number)
{
//    for(uint i = 0; i < this->size(); i++) {
//        std::cout << this->operator[](i) << ' ';
//    }
    std::stringstream ss;
    const auto& vRef = functionSet_->vActiveFunctions_;
    std::deque<uint> working_deque;
    uint start_index = this->size() - nOutputs + output_number;
    uint start_value = this->operator[](start_index).value;
    working_deque.push_back(start_value);
//    std::cout << "start_index: " << start_index << " " << start_value << '\n';
//    std::cout << "nInputs: " << nInputs << '\n';
    while(!working_deque.empty()) {
        uint working_index = working_deque.front();
//        std::cout << "wotking index: " << working_index << '\n';
        working_deque.pop_front();
        if(working_index >= nInputs) {
//            std::cout << "U trail stavio: " << (working_index - nInputs) << '\n';
            const auto& gene = this->at(working_index - nInputs);
            ss << vRef[gene.value]->getName() << "(";
            
            if(gene.isOutput) {
                std::cout << "Something went wrong. Trail is considering an output index.\n";
            }
            for(const auto& elem : gene.inputConnections) {
//                std::cout << "\t\tPlacing element: " << elem << '\n';
                ss << elem << ", ";
                working_deque.push_back(elem);
            }
            ss << ")" << std::endl;
        }
    }
    return "TODO: ss to string";
}

std::string Cartesian::toStringAllActiveNodes()
{
    std::stringstream ss;
    ss.str("");
    ss.clear();
    for(uint i = 0; i < nOutputs; i++) {
        ss << toStringActiveNodes(i);
    }
    return "TODO";
}


void Cartesian::evaluate(const std::vector<double> &inputData, std::vector<double> &results)
{
//    for(uint i = 0; i < this->size(); i++) {
//        std::cout << this->operator[](i) << ' ';
//    }
//    std::cout << '\n' << "Kraj ispisa genoma.\n";
    std::vector<double> working_vector(inputData);
//    std::cout << "Ovo mu je input za evaluaciju.###\n";
//    for(const auto& elem: working_vector) {
//        std::cout << elem << ' ';
//    }
//    std::cout << "Checkpoint #1.\n";

    // Add constants to working vector
    for (auto c : this->constantSet) {
        working_vector.push_back(c);
    }

    std::vector<double> operands;
    const auto& vRef = functionSet_->vActiveFunctions_;
    double result = 0;

    for(uint i = 0; i < this->size() - nOutputs; i++) {
        const auto& gene = this->operator[](i);
//        std::cout << "Gen rednog broja: " << i << " funkcija tipa: " << gene.value << " broj konekcija: " << gene.inputConnections.size() << " je li izlazni: " << gene.isOutput << '\n';
        for(const auto& elem : gene.inputConnections) {
            operands.push_back(working_vector[elem]);
        }
//        std::cout << "Veličina operanada: " << operands.size() << '\n';
//        for(const auto& elem: operands) {
//            std::cout << "op: " << elem << ' ';
//        }
        vRef[gene.value]->evaluate(operands,result);
//        std::cout << "Rezultat operacije evaluacije je: " << result << '\n';
        working_vector.push_back(result);
        operands.clear();
        result = 0;
    }
    for(uint i = this->size() - nOutputs; i < this->size(); i++) {
        results.push_back(working_vector[this->operator[](i).value]);
    }
//    std::cout << "\n2# Konačno rezultati su: \n";
//    for(const auto& elem : results) {
//        std::cout << elem << ' ';
//    }
//    std::cout << '\n';
    for(const auto& elem : results) {
        if(std::isnan(elem) || std::isinf(elem)) {
            std::cout << "Dogodio se nan ili inf.\n";
                for(uint i = 0; i < this->size(); i++) {
                    std::cout << this->operator[](i) << ' ';
                }
                std::cout << '\n';
                for(const auto& elem2: inputData) {
                    std::cout << elem2 << ' ';
                }
                std::cout << '\n';
                std::cout << "\n2# Konačno rezultati su: \n";
                for(const auto& elem3 : results) {
                    std::cout << elem3<< ' ';
                }
                std::cout << '\n';
                exit(-1);
        }
    }
}
}

