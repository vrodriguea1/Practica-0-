int RedCar= 12; //LUZ ROJA DEL CARRO
int GreenCar= 10; //LUZ VERDE DEL CARRO 
int YeCar= 11; //LUZ AMARILLA DEL CARRO 
int RedPe= 4;  //LUZ ROJA PEATON 
int GreenPe= 3; //LUZ VERDE PEATON 
int pul= 7;  //BOTON 
int cont=0; // variable contador 


void setup(){
  //se defiene los LEDs como salidas, se inicializa el serial
  Serial.begin(9600);
  pinMode(RedCar,OUTPUT);
  pinMode(GreenCar,OUTPUT);
  pinMode(YeCar,OUTPUT);
  pinMode(RedPe,OUTPUT);
  pinMode(GreenPe,OUTPUT);

  // se define el boton como salidas 
  pinMode(pul,INPUT);

 //digitalWrite(RedPe,HIGH); 
 //digitalWrite(GreenCar,HIGH);
  
}

void Semaforo() {                                // la luz verde de los carros encendida, durante 85 segundos,cuando va a cambiar de estado papadea 5 veces antes de cambiar a amarrillo...
                                                 // ... todo esto mientras el rojo peatonal esta encendido  
 digitalWrite(RedPe,HIGH); 
 digitalWrite(GreenCar,HIGH);
 delay(85000);
 digitalWrite(GreenCar,LOW);
 delay(1000);
 digitalWrite(GreenCar,HIGH);
 delay(1000);
 digitalWrite(GreenCar,LOW);
 delay(1000);
 digitalWrite(GreenCar,HIGH);
 delay(1000);
 digitalWrite(GreenCar,LOW);
 delay(1000);



 //  se enciende el led amarillo, con una duracion de 5 segundos, se apaga el semaforo rojo peatonal, se prende el semaforo rojo de carros...
 // ...  se enciende el verde peatonal y se pone a parpadear 5 veces
 digitalWrite(YeCar,HIGH); 
 delay(5000);
 digitalWrite(RedPe,LOW);
 digitalWrite(YeCar,LOW); 
 digitalWrite(GreenPe,HIGH); 
 digitalWrite(RedCar,HIGH);
 delay(20000);
 digitalWrite(GreenPe,HIGH);
 delay(15000);
 digitalWrite(GreenPe,LOW);
 delay(1000);
 digitalWrite(GreenPe,HIGH);
 delay(1000);
 digitalWrite(GreenPe,LOW);
 delay(1000);
 digitalWrite(GreenPe,HIGH);
 delay(1000);
 digitalWrite(GreenPe,LOW);
 delay(1000);
 digitalWrite(RedPe,HIGH);
 delay(2000);
 digitalWrite(RedCar,LOW);       // pasar a verde el vehicular deberá haber pasado al menos 2 segundos desde el instante en que el peatonal haya cambiado a rojo.
 digitalWrite(RedPe,HIGH);
 digitalWrite(GreenCar,HIGH);
 delay(2000);
}


void puls(){
// se deinen un contador para os puslsos recibidos por el boton 
  if ( digitalRead(pul)==HIGH)  
  {
  if ( digitalRead(pul)==LOW)     // definimos primero HIGH y uego el LO, para que lo cuente solo cuando se presion y se suelte 
  {
    cont++;                       // se suman en la varibale anteriromente mencionadas 
    Serial.println(cont);          // aquí podemos visualizra los pulsos 
    delay(1000);
  }
  }

 if ((cont==5))                 // se pone la condidcion la cual nos dice que si los pulsos son iguales a cinco 
{
 digitalWrite(RedPe,HIGH);      //el peatonal en rojo, el verde de arros titila, luego pasa a naranja, despues a rojo del carro 
 digitalWrite(GreenCar,HIGH);   // y se pasa a verde del peatonal
 for (int x=0; x<5; x++)        // en este for se dine el parpadeo del led 5 veces 
 {
 digitalWrite(GreenCar,HIGH);
 delay(1000);
 digitalWrite(GreenCar,LOW);
 delay(1000);
 }
 digitalWrite(YeCar,HIGH);
 digitalWrite(YeCar,LOW);
 digitalWrite(RedCaR,HIGH);
 delay(2000);
 digitalWrite(GreenPe,HIGH);
 
 }
}


void loop(){
  
  Semaforo(); // Se llamamos esta funcion ya que, se reinicio el sistema, y esta es la que realiza todo el procedimiento
}   
