#include "../header/Specimen.hpp"

uint Specimen::net_size = 0;
uint Specimen::inputs = 0;
uint Specimen::outputs = 0;
uint Specimen::neuro_size = 0;
uint Specimen::num_neurons = 0;
int* Specimen::types = NULL;
double** Specimen::dataset = NULL;
uint Specimen::dataset_size = 0;

Specimen::Specimen(double **dataset, uint dataset_size){
    //basic
    this->acuracy = 0;

    //dataset
    this->dataset = dataset;
    this->dataset_size = dataset_size;

    //copy
    this->inputs = io::configs.inputs;
    this->outputs = io::configs.outputs;
    this->num_neurons = io::configs.num_neurons;
    this->types = io::configs.types;

    //size definitions
    uint neuro_size = 0;
    neuro_size += io::configs.inputs;
    neuro_size += io::configs.outputs;

    this->neuro_size = neuro_size;
    this->net_size = neuro_size * io::configs.num_neurons;

    this->net = (double*)calloc(net_size, sizeof(double));
    this->inter = (double*)calloc(outputs, sizeof(double));
}

Specimen::Specimen(string seed_inter, double **dataset, uint dataset_size){
    //basic
    this->acuracy = 0;

    //dataset
    this->dataset = dataset;
    this->dataset_size = dataset_size;

    //copy
    this->inputs = io::configs.inputs;
    this->outputs = io::configs.outputs;
    this->num_neurons = io::configs.num_neurons;
    this->types = io::configs.types;

    //size definitions
    uint neuro_size = 0;
    neuro_size += io::configs.inputs;
    neuro_size += io::configs.outputs;

    this->neuro_size = neuro_size;
    this->net_size = neuro_size * io::configs.num_neurons;

    this->net = (double*)calloc(net_size, sizeof(double));
    this->inter = (double*)calloc(outputs, sizeof(double));

    uint seed = std::stoi(seed_inter);
    srand(seed);
    for(uint i = 0; i < net_size; i++)
        net[i] = (double)(rand()%100) / 100;
}

Specimen::~Specimen(){
}


double Specimen::mimAbsError(){
    return 0;
}

double Specimen::mimRelError(){
    return 0;
}

double Specimen::mimSquaAbsError(){
    return 0;
}

double Specimen::mimSquaRelError(){
    return 0;
}

string Specimen::getNeural(){
    return "0";
}

double Specimen::testAcuracy(){
    return 0;
}

double Specimen::execute(double *valor){
    for(uint j = 0; j < outputs; j++){
        inter[j] = 0;
    }

    for(uint i = 0; i < num_neurons; i++){
        uint shift = i * neuro_size;
        double input = 0;
        for(uint j = 0; j < inputs; j++){
            input += net[shift + j] * valor[j];
        }
        shift += inputs;
        for(uint j = 0; j < outputs; j++){
            if(types[i] == 0)
                inter[j] += 100 * net[shift + j] * input;
            else
                inter[j] += 100 * net[shift + j] * input*input;
        }
    }
    double erro = 0;
    for(uint j = 0; j < outputs; j++){
        erro += abs(inter[j] - valor[j + inputs]) * abs(inter[j] - valor[j + inputs]);
    }
    return erro;
}

void Specimen::evaluate(){
    double error_total = 0;
    for(uint i =0; i < 2*dataset_size/3;i++){
        error_total += execute(dataset[i]);
    }
    this->acuracy = error_total/(2*dataset_size/3);
}

void Specimen::recreate(Specimen &pg1, Specimen &pg2){
    uint neurons_pg1 = ceil(num_neurons/2);
    uint neurons_pg2 = num_neurons - neurons_pg1;

    for(uint i = 0; i < neurons_pg1 * neuro_size; i++)
        if(rand()%10 > 6){
            this->net[i] = ((double)((int)ceil(pg1.net[i] * 100 + rand()%100)%100))/100;
        }else{
            this->net[i] = pg1.net[i];
        }

    for(uint i = neurons_pg1 * neuro_size; i < net_size; i++)
        if(rand()%10 > 6)
            this->net[i] = ((double)((int)ceil(pg2.net[i] * 100 + rand()%100)%100))/100;
        else
            this->net[i] = pg2.net[i];
}

bool Specimen::compare(const Specimen &po1, const Specimen &po2){
    return po1.acuracy < po2.acuracy;
}
