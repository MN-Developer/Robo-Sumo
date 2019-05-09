
// Data de modificação 04/05/2019.

// Autor Mateus Gabriel da Silva 

// Ciência da Computação 3º Semestre. 

// Tudo OK.

// ------------------ Definindo Variaveis e portas ------------------------------

#define velmotordir 6

#define velmotoresq 5

#define saida 13

#define entrada A5

int estado = 0;

const byte me1 = 9; 

const byte me2 = 10;

const byte md1 = 11;

const byte md2 = 12;

int veldir = 0;

int velesq = 0;

const byte sfe = 7;

const byte sfd = 8;

const byte sff = 2;

const int trigfrente = 4;

const int echofrente = 3;

const int trigdir = A2;

const int echodir = A1;

const int trigesq = A4;

const int echoesq = A3;

int distanciaFrente = 0;

int distanciaDireita = 0;

int distanciaEsquerda = 0;

unsigned long tempo = 0;

unsigned long tempoAnterior = 0;

boolean estadosfe;

boolean estadosfd;

boolean estadosff;

// ------------------ Ajustando o Setup ------------------------------


void setup() {

	Serial.begin(9600);

  // ------------------ Setando os pinos do Botão de inicio de partida e Led 5 segundos ------------------------------

	pinMode(entrada, INPUT);
	pinMode(saida, OUTPUT);
	digitalWrite(saida,LOW);

  // ------------------ Definindo os pinos dos Motores como Saida ------------------------------
	
	pinMode(me1, OUTPUT);
	pinMode(me2, OUTPUT);
	pinMode(md1, OUTPUT);
	pinMode(md2, OUTPUT);

  // ------------------ Definindo a saida PWM do motor que definira a Velocidade do mesmo ------------------------------

	pinMode(velmotordir, OUTPUT);
	pinMode(velmotoresq, OUTPUT);

  // ------------------ Definindo os Sensores de Faixa como entrada ------------------------------
	
	pinMode(sfe, INPUT);
	pinMode(sfd, INPUT);
	pinMode(sff, INPUT);

  // ------------------ Definindo os Sensores Ultrassonicos como entrada ------------------------------
	
	pinMode(trigfrente, OUTPUT);
	pinMode(echofrente, INPUT);
	pinMode(trigdir, OUTPUT);
	pinMode(echodir, INPUT);
	pinMode(trigesq,OUTPUT);
	pinMode(echoesq,INPUT);
}

// ------------------ Função Andar Frente com 50% do motor ------------------------------

void andarFrente50(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 130;
	velesq = 130;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me1, LOW);
	digitalWrite(me2, HIGH);
	digitalWrite(md1, LOW);
	digitalWrite(md2,HIGH); 
}

// ------------------ Função Andar Frente com 100% do motor ------------------------------

void andarFrente100(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 255;
	velesq = 255;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me1, LOW);
	digitalWrite(me2, HIGH);
	digitalWrite(md1, LOW);
	digitalWrite(md2,HIGH); 
}

// ------------------ Função Andar para Tras ------------------------------

void andarTras(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 255;
	velesq = 255 ;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me2, LOW);
	digitalWrite(me1, HIGH);
	digitalWrite(md2, LOW);
	digitalWrite(md1,HIGH); 
}

// ------------------ Função Virar para Esquerda ------------------------------

void virarEsq(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 255;
	velesq = 255;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me1, LOW);
	digitalWrite(me2, LOW);
	digitalWrite(md1, LOW);
	digitalWrite(md2,HIGH); 
}

// ------------------ Função Virar para Direita ------------------------------

void virarDir(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 255;
	velesq = 255;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me1, LOW);
	digitalWrite(me2, HIGH);
	digitalWrite(md1, LOW);
	digitalWrite(md2, LOW); 
}

// ------------------ Função Parar ------------------------------

void parar(){

	// ------------------ Define a Velocidade do Motor ------------------------------
	veldir = 255;
	velesq = 255;
	
	analogWrite(velmotordir, veldir);
	analogWrite(velmotoresq, velesq);

	digitalWrite(me1, LOW);
	digitalWrite(me2, LOW);
	digitalWrite(md1, LOW);
	digitalWrite(md2, LOW); 
}

// ------------------ Função Ultrassom Dianteiro ------------------------------

int ultrassomFrente(){
	long duracao;
	digitalWrite(trigfrente,LOW);
	delayMicroseconds(2);
	digitalWrite(trigfrente, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigfrente, LOW);
	duracao = pulseIn(echofrente, HIGH);
	distanciaFrente = (duracao/2) / 29.1;
	return(distanciaFrente);
}

// ------------------ Função Ultrassom Direito ------------------------------

int ultrassomDireito(){
	long duracao;
	analogWrite(trigdir,0);
	delayMicroseconds(2);
	analogWrite(trigdir, 255);
	delayMicroseconds(10);
	analogWrite(trigdir, 0);
	duracao = pulseIn(echodir, 255);
	distanciaDireita = (duracao/2) / 29.1;
	return(distanciaDireita);
}

// ------------------ Função Ultrassom Esquerdo ------------------------------

int ultrassomEsquerdo(){
	long duracao;
	analogWrite(trigesq,0);
	delayMicroseconds(2);
	analogWrite(trigesq, 255);
	delayMicroseconds(10);
	analogWrite(trigesq, 0);
	duracao = pulseIn(echoesq, 255);
	distanciaEsquerda = (duracao/2) / 29.1;
	return(distanciaEsquerda);
}

// ------------------ Função Lutar ------------------------------

void lutar(){

	andarFrente50();
	
	tempoAnterior = millis();

	while( tempo < 900000){

		estadosfe = digitalRead(sfe);
		estadosfd = digitalRead(sfd);
		estadosff = digitalRead(sff);

		ultrassomFrente();
		ultrassomDireito();
		ultrassomEsquerdo();

    // ------------------ Testando as Condições para o Combate ------------------------------

		if(estadosfe == 0 || estadosfd == 0){
			andarTras();
		}

		else if(estadosff == 0){
			andarFrente50();
		}

		else if(distanciaFrente <= 15){
			andarFrente100();
		}

		else if(distanciaDireita <= 15){
			virarDir();
		}

		else if(distanciaEsquerda <= 15){
			virarEsq();
		}

		tempo = millis() - tempoAnterior;
	}

	while(true){
		parar();
	}
	
}

// ------------------ Aguarda 5 segundos após aperto do Botao de Start ------------------------------

void esperar(){

	estado = analogRead(entrada);
	if(estado == 1000){

		digitalWrite(saida,HIGH);
		delay(5000);
		digitalWrite(saida,LOW);

		lutar();
	}
}

// ------------------ Chama a função Esperar para fazer todo procedimento da Luta ------------------------------

void loop() {
	esperar();
}