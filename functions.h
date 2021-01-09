#define FUNCTIONS_H

int calculaConvidados(int *pConvidados, int parada);

float calculaPercentual(float parcela, float total);

float calculaGarcon(float *custos, int *convidados);

float calculaComida(float *custos, int *convidados);

void compilaGastos(float orcamento, int *convidados);

int comparaString(char primeiraString[30], char segundaString[30]);

void gastosExtras();

void ordenaAlfabetica(char **conv, int *quantConvFam, int parada);

void calculaBebidas(int *convidados);

void divideMesas(int *convidados);

