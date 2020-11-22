int convidados[3];

//essa fun��o soma a quantidade de convidados
//ela recebe como parametro uma variavel com o valor de parada
//esse valor de parada vai indicar at� que casa do vetor ele vai somar
//exemplo pra gar�om somamos todas as casas,
// pq precisamos do total de convidados, ent�o passamos 3
//j� pra comida somamos as 2 primeiras, pq primeiro queremos a quantidade de adultos
int calculaConvidados(int *pConvidados, int parada){ 
	int totalConvidados = 0, i;
    for(i=0; i < parada; i++) {
     totalConvidados = totalConvidados + pConvidados[i];
    }
    return totalConvidados;
}


//recebe como parametro a parcela e o total
//calcula quantos % a parcela � do total
//retorna o resultado
 float calculaPercentual(float parcela, float total) {
      float percentual = (parcela / total) * 100;
      return percentual;
  }

//essa fun��o recebe como parametro os custos, para atualizar o valor
//chama a fun��o que calcula o total de convidados, passa 3 de parametro
//divide o numero de convidados que retornou por 50
// e arredonda pra cima
//multiplica o resultado por 100 que � o custo de cada gar�om
void calculaGarcon(float *custos){
	int parada = 3;
	int conv = calculaConvidados(&convidados, parada);
    float garcon = conv / 50.0;
    int retorno = ceil(garcon);
    float custoGarcons = retorno * 100.00;
    *custos = *custos + custoGarcons;
}

//essa fun��o recebe como parametro os custos, para atualizar o valor
//aqui chama a fun��o de calcular convidados e passa 2 como parametro
//pq s� queremos os adultos
//depois multiplica o numero de adultos por 25 que � o pre�o do buffet
// multiplica o numero de criancas por 12.5 que � o pre�o do buffet
//soma os 2 resultados e atualiza a variavel custos
void calculaComida(float *custos) {
	int parada = 2;
	int convAdulto = calculaConvidados(&convidados, parada);
	int convCrianca = convidados[2];
	float custoTotalComida = convAdulto * 25.00 + convCrianca * 12.50;
	*custos = *custos + custoTotalComida;
}

//Nessa fun��o eu chamo as fun��es que calculam comida e gar�ons 
//as fun��es que calculam a comida e a quantidade de gar�ons atualiam a variavel gastos
//verifica se os gastos s�o maiores que o or�amento, se forem avisa que ultrapassou
// se os gastos forem iguais avisa que zerou
// se forem menores:
//subtrai valor de gastos do or�amento
//chama a fun��o de percentual pra calcular quantos % do orcamento sobra
//mostra quanto gastou, quanto sobrou e quanto % sobrou
 void compilaGastos(float orcamento) {
      float gastos;
      calculaGarcon(&gastos);
      calculaComida(&gastos);
      
      if(orcamento > gastos) {
	      float orcamentoRestante = orcamento - gastos;
	      float percent = calculaPercentual(orcamentoRestante, orcamento);
	      printf("\n vc vai gastar %.2f", gastos);
	      printf("\n sobra %.2f", orcamentoRestante);
	      printf("\n sobra %.2f por cento", percent);
	  } else if(orcamento == gastos) {
	  	printf("\n vc zerou seu orcamento nao pode mais gastar\n");
	  } else if(orcamento < gastos) {
	  	printf("\n ops os gastos ultrapassaram o orcamento \n");
	  }

  }


//aqui o usuario insere os dados, quantidade de convidados � inserida em um vetor dividido por idade e sexo 
// separados por sexo e idade, pq na hr de calcular a bebida e a comida a idade e o sexo fazem diferen�a
//pergunta ao usu�rio o or�amento que ele tem pra festa
//chama a a fun��o que compila os gastos, a fun��o compila gastos recebe o orcamento como parametro
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
    compilaGastos(orcamento);
}
