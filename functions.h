int convidados[3];

int calculaConvidados(int *pConvidados, int parada){ 
	int totalConvidados = 0, i;
    for(i=0; i < parada; i++) {
     totalConvidados = totalConvidados + pConvidados[i];
    }
    return totalConvidados;
}


void calculaGarcon(float *custos){
	int parada = 3;
	int conv = calculaConvidados(&convidados, parada);
    float garcon = conv / 50.0;
    int retorno = ceil(garcon);
    float custoGarcons = retorno * 100.00;
    *custos = *custos + custoGarcons;
}

void calculaComida(float *custos) {
	int parada = 2;
	int convAdulto = calculaConvidados(&convidados, parada);
	int convCrianca = convidados[2];
	float custoTotalComida = convAdulto * 25.00 + convCrianca * 12.50;
	*custos = *custos + custoTotalComida;
}

  float calculaPercentual(float parcela, float total) {
      float percentual = (parcela / total) * 100;
      return percentual;
  }

  float calculaGastos(float orcamento) {
      float gastos;
      calculaGarcon(&gastos);
      calculaComida(&gastos);
      float orcamentoRestante = orcamento - gastos;
      float percent = calculaPercentual(orcamentoRestante, orcamento);
      printf("\n vc vai gastar %.2f", gastos);
      printf("\n sobra %.2f", orcamentoRestante);
      printf("\n sobra %.2f por cento", percent);
  }



void recebeDadosDoEvento() {
    float orcamento;
    printf("\n informe quantos homens adultos estao convidados\n");
    scanf("%d", &convidados[0]);
    printf("\n informe quantas mulheres adultas estao convidadas\n");
    scanf("%d", &convidados[1]);
    printf("\n informe quantas criancas estao convidadas\n");
    scanf("%d", &convidados[2]);
    printf("\nInforme o orcamento do evento\n");
    scanf("%f", &orcamento);
    calculaGastos(orcamento);
}


