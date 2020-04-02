//Definicion de los pines
uint8_t RedCar= 12; // LED ROJA DEL CARRO
uint8_t GreenCar= 11; // LED VERDE DEL CARRO 
uint8_t YeCar= 10; // LED AMARILLA DEL CARRO 
uint8_t RedPe= 4;  // LED ROJA PEATON 
uint8_t GreenPe= 3; // LED VERDE PEATON 
uint8_t Pul= 7;  // PULSADOR

//Las siguientes variables se declaran fuera de todas las funciones ya que estas se usan en dos funciones diferentes
uint8_t Contador = 0;  // Contador de veces que se oprime el pulsador
uint8_t EstadoAnterior = 0; // Estado anterior del pulsador
uint8_t ValorPul = 0; // Estado del pulsador, se inicializa en 0

void setup(){

  // Se configura el pulsador como entrada
  pinMode(Pul, INPUT); 
  
  // Se configuran los LEDs como salida 
  pinMode(RedCar, OUTPUT); 
  pinMode(GreenCar, OUTPUT); 
  pinMode(YeCar, OUTPUT); 
  pinMode(RedPe, OUTPUT); 
  pinMode(GreenPe, OUTPUT); 

  // Se definen las condiciones iniciales = caso 0 (semáforo vehicular en verde y peatonal en rojo)
  digitalWrite(GreenCar, 1); // LED verde vehicular encendido 
  digitalWrite(RedPe, 1); // LED rojo peatonal encendido
  digitalWrite(YeCar, 0); // LED amarillo vehicular apagado
  digitalWrite(RedCar, 0); // LED rojo vehicular apagado
  digitalWrite(GreenPe, 0); // LED verde peatonal apagado
  
}

enum Estado { // Se "enumeran" los casos posibles de la variable Estado, que es la que se esta comparando en cada case
  uno,
  dos,
  tres,
  cuatro,
  cinco,
  seis
};

int Pulsaciones(){ // Funcion que cuenta cuando se oprime el pulsador
  
ValorPul = digitalRead(Pul); // Se lee el estado del pulsador

 if(ValorPul != EstadoAnterior){  // Se pregunta si los valores son diferentes
  	if(ValorPul == 1){        
    		Contador++;              // Si el pulsador fue oprimido el contador va sumando 1
  		}
      	if(ValorPul == 0){      // Si el pulsador no se oprime no se empieza a contar
      	}
	}
EstadoAnterior = ValorPul; // Se guarda el estado actual del pulsador para la siguiente iteracion
	return Contador; // Me arroja un entero
}

void Semaforo(){
  
	static uint8_t Estado = 0; // Estado del diagrama
	static uint32_t Reloj = 0; // Reloj relativo para poder hacer diferencias de tiempo
 	static uint32_t Wink_Reloj = 0; // Contador para el estado "led verde titilando"
	static uint8_t Wink_Contador = 0; // Contador de las titiladas
  
switch(Estado){
    	
   case uno : // Estado S1 (estado inicial) : vehicular en verde y peatonal en rojo
      		
      Pulsaciones(); // Se llama esta funcion para verificar el valor del contador
      if(millis()-Reloj >= 85000){ // Se cuentan 85 seg antes de pasar al siguiente estado
       	Estado = 1;
     		}
      	if(Contador >= 5){ // Cuando se oprime el pulsador 5 veces pasa al siguiente estado (LED verde titilando)
        	Estado = 1;
          Reloj = millis()-85000; //Ajuste para que justo cuando millis()-reloj sea igual a 85s se pase al estado S2
      		}
         
      		break;
      
    case dos : // Estado S2 : LED verde vehicular titilando
			
     	 if(millis()-Wink_Reloj >= 1000 && millis()-Reloj >= 5000){ // Se enciende y apaga el LED verde vehicular cada segundo por 5 seg
       digitalWrite(GreenCar, !digitalRead(GreenCar));
       Wink_Reloj = millis();
       Wink_Contador++; // Cada que se encience o apaga, aumentamos el contador de las titiladas
     		}
      		
      	if(Wink_Contador >= 10){ // Si el LED se enciende 5 veces se pasa al estado S3 
          Estado = 2;
          Wink_Contador = 0;
      		}
         
     break; 
         
     case tres : // Estado S3 : Se enciende el vehicular amarillo
      		
      	digitalWrite(GreenCar,0); // Se apaga el LED verde 
      	digitalWrite(YeCar,1); // Se enciende en LED amarillo 
      		
      	if(millis()-Reloj >= 5000){ // Se cuentan 5 seg con el LED amarillo encendido
          Estado = 3;
          Reloj = millis();
     		}
        
      break;
          
      case cuatro : // Estado S4 : Se encienden los LEDs rojo vehicular y verde peatonal
      		
      	digitalWrite(YeCar,0); // Se apaga el LED amarillo vehicular
        digitalWrite(RedPe,0); // Se apaga el LED rojo peatonal
      	digitalWrite(RedCar,1); // Se enciende el LED rojo vehicular
      	digitalWrite(GreenPe,1); // Se enciende el LED verde peatonal
      		
      	if(millis()-Reloj >= 15000){ // Se cuentan 15 seg con el rojo vehicular encendido
        	Estado = 4;
          Reloj = millis();
      		}
         
      break;
          
      case cinco : // Estado S5 : LED verde peatonal titilando
     		
     		if(millis()-Wink_Reloj >= 1000 && millis()-Reloj >= 5000){ // Se enciende y apaga el LED verde peatonal cada segundo por 5 seg
        	digitalWrite(GreenPe, !digitalRead(GreenPe));
          Wink_Reloj = millis();
          Wink_Contador++; // Cada que se encience o apaga, aumentamos el contador de las titiladas
     		}
      		
      		if(Wink_Contador >= 10){ // Si el LED se enciende 5 veces pasa al siguiente estado
            Estado = 5;
            Reloj = millis();
      		}
         
     break; 
         
		 case seis : // Estado S6 (ultimo estado antes de reiniciar) : Se apaga el LED verde peatonal y se enciende el rojo peatonal
      		
      	digitalWrite(GreenPe,0); // Se apaga el LED verde peatonal
      	digitalWrite(RedPe,1); // Se enciende el LED rojo peatonal
      		
      	if(millis()-Reloj >= 2000){ // Se esperan 2 seg antes de que ocurra el Estado S1 (LED vehicular rojo se apague y se encienda el LED vehicular verde)   
        		
         Estado = 0;             // Se reinicia todo el sistema 
         Reloj = millis();		  
               
         digitalWrite(RedCar,0); // Se apaga el LED rojo vehicular
         digitalWrite(GreenCar,1); // Se enciende el LED verde vehicular
              	
         Contador = 0;     // Como se reinicio todo el sistema estas variables se vuelven a inicializar
				 EstadoAnterior = 0;
				 ValorPul = 0; 
				 Wink_Contador = 0;
      		}
         
      break;
      			
    }
}

void loop(){
  
Semaforo(); // Se llamamos esta funcion ya que, se reinicio el sistema, y esta es la que realiza todo el procedimiento

}  
  
