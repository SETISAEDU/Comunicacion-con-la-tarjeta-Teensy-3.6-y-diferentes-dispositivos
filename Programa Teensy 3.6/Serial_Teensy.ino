//PROGRAMA PRINCIPAL//

const int SetPin = 2; //pin de configuracion para el APC220
const int EchoPin = 3; //pin digital para el echo del sensor ultrasonico
const int TriggerPin = 4; //pin digital para el trigger del sensor ultrasonico
const int Button_1Pin=5; //Pulsador designado para la comunicacion con los APC220
const int Button_2Pin=11; //Pulsador designado para los eventos del puerto serial 4
const int Button_3Pin=12; //Pulsador designado para los eventos del puerto serial 5
const int LED_bt=6; //Indicador con el bluetooth
unsigned char BluetoothData; //Datos reibidos del dispositivo bluetooth
long debouncing_time1 = 100; //Tiempo de espera para evitar los rebotes
long debouncing_time2 = 100;
long debouncing_time3 = 100;
volatile unsigned long last_micros1; //Variable para guargar el valor de la ultima lectura de tiempo
volatile unsigned long last_micros2;
volatile unsigned long last_micros3;
#define event_1 0x10 
#define event_2 0x20

bool send_button_1=false,send_button_2=false,send_button_3=false; //banderas para el envio de datos a los dispositivos
bool apagar_led_bt=false, enceder_led_bt=false; //Banderas para el control de la secuencia de accion de los pulsadores
bool apagar_led=false, enceder_led=false;
bool apagar_led2=false, enceder_led2=false;
bool apagar_led3=false, enceder_led3=false;

void setup() {
 
 Serial.begin(57600);                            //Solo para depuracion
 Serial1.begin(57600);                           //Comunicacion serial con el módulo APC 220
 Serial2.begin(57600);                           //Comunicacion serial con el módulo HC-05 (SETISAEDU)
 Serial3.begin(57600);                           //Comunicacion serial con el segundo módulo HC-05 (SETISAEDU2) 
 Serial4.begin(9600);                            //Comunicacion serial con el ARDUINO MEGA
 Serial5.begin(9600);                            //Comunicacion serial con el ARDUINO MEGA
 pinMode(LED_bt,OUTPUT);                         //Modo de los pines digitales
 pinMode(TriggerPin, OUTPUT);                    
 pinMode(EchoPin, INPUT);
 pinMode(SetPin, OUTPUT);                         //Configuracion de pin de control para el modulo como salida
 
  //Configuracion de pines para los LED como salidas
 pinMode(Button_1Pin, INPUT_PULLUP); 
 pinMode(Button_2Pin,INPUT_PULLUP);
 pinMode(Button_3Pin,INPUT_PULLUP);

 digitalWrite(SetPin, HIGH);                      //Inicializacion del pin de control SET en alto
 ConfigAPC();                                     //Configuracion del modulo APC 220

 attachInterrupt(digitalPinToInterrupt(5), Interrupt1, FALLING); //Interrupcion para el Serial1
 attachInterrupt(digitalPinToInterrupt(11),Interrupt2, FALLING); //Interrupcion para el Serial4
 attachInterrupt(digitalPinToInterrupt(12),Interrupt3, FALLING); //Interrupcion para el Serial5
 
}


void loop() {
                                        //Evaluacion de banderas para el envio de datos
  if(send_button_1==true)
  {
    if(enceder_led == true)
    {
    
    Serial1.write(event_1);             //Envio de los valores a los otros modulos, con la direccion correspondiente
    apagar_led=true;
    send_button_1=false;                //Reestablecimiento de la bandera a falso despues de haber completado el envio
  
  }
    if(enceder_led==false)
    {
     Serial1.write(event_2);         
     apagar_led=false;
     send_button_1=false;               
    }
}
  
  if(send_button_2==true)
  {
    if(enceder_led2 == true)
    {
    
    Serial4.write('A'); 
    apagar_led2=true;
    send_button_2=false;             
  
  }
    if(enceder_led2==false)
    {
     Serial4.write('B'); 
     apagar_led2=false;
     send_button_2=false;          
    }
  }

  if(send_button_3==true)
  {
    if(enceder_led3 == true)
    {
   
    Serial5.write('C'); 
    apagar_led3=true;
    send_button_3=false; 
  
  }
    if(enceder_led3==false)
    {
     Serial5.write('D'); 
     apagar_led3=false;
     send_button_3=false; 
    }
  }

  
  if (Serial2.available())
  {
    BluetoothData=Serial2.read();                   //Lectura del puerto serial numero 2
    
    if(BluetoothData=='G')                          //Si el dato recibido es el caracter G
    {
      digitalWrite(LED_bt,HIGH);
    }
    else if(BluetoothData=='R')                      //Si el dato recibido es el caracter R
    {
      digitalWrite(LED_bt,LOW);
    }
  }


 int cm = ping(TriggerPin, EchoPin);                  //Función especial para calcular la distancia de un objeto
 Serial3.print("*D");                                //Manda el dato de *D segudo de la distancia mas *
 Serial3.print(String(cm));
 Serial3.print("*");
 delay(200);

}

void Interrupt1() { 
  if ((long)(micros() - last_micros1) >= debouncing_time1 * 1000)     //Función para evitar el efecto de rebote en los pulsadores
  {
    if (apagar_led ==false)
    {
    send_button_1=true; 
    enceder_led = true;
   last_micros1 = micros();
    }
  else if(apagar_led ==true)
  {
    send_button_1=true; 
    enceder_led=false;
    last_micros1 = micros();
  }
}
Serial.print("Pulso");
}
  
void Interrupt2() { 
  
  if ((long)(micros() - last_micros2) >= debouncing_time2 * 1000) 
  {
    if (apagar_led2 == false)
    {
    send_button_2=true; 
    enceder_led2 = true;
    last_micros2 = micros();
    }
  else if(apagar_led2 ==true)
  {
    send_button_2=true; 
    enceder_led2=false;
   
    //last_micros2 = micros();
  }
 }
     Serial.print("pulso");
}
void Interrupt3() { 
  if ((long)(micros() - last_micros3) >= debouncing_time3 * 1000) 
  {
    if (apagar_led3 == false)
    {
    send_button_3=true; 
    enceder_led3 = true;
    last_micros3 = micros();
    
    }
  else if(apagar_led3 ==true)
  {
    send_button_3=true; 
    enceder_led3=false;
    last_micros3 = micros();
  }
}
}
 
 int ping(int TriggerPin, int EchoPin) 
 {
 long duration, distanceCm;
 
   digitalWrite(TriggerPin, LOW);                //para generar un pulso limpio ponemos a LOW 4us
 delayMicroseconds(4);
 digitalWrite(TriggerPin, HIGH);                  //generamos Trigger (disparo) de 10us
 delayMicroseconds(10);
 digitalWrite(TriggerPin, LOW);
 
 duration = pulseIn(EchoPin, HIGH);              //medimos el tiempo entre pulsos, en microsegundos
 
 distanceCm = duration * 10 / 292/ 2;             //convertimos a distancia, en cm
 return distanceCm;
}

//Funcion de configuracion del modulo APC220
void ConfigAPC() 
{
                                                    // Procedimiento de configuración a 450MHz
    Serial.println("Configurando a 450MHz ...");
    digitalWrite(SetPin, LOW);                      //Escritura en bajo del pin SET
    delay(2);                                       //Espera necesaria antes de poder enviarle comandos
    Serial1.end();
    Serial1.begin(9600);                            //Cambio de velocidad del UART, a la velocidad de configuracion
    Serial1.println("WR 450000 4 9 6 0");           //Envio de datos de configuracion
    delay(201);                                     //Espera antes de la respuesta por parte del modulo

    if (Serial1.available())                         //Verificacion de que el modulo a contestado
    {
      String data = Serial1.readString();
      Serial.println(data);                          //Solo para depuracion
    }
    digitalWrite(SetPin, HIGH);                      //Restablecimiento del pin al valor de alto
    delay(11);                                       //Espera antes de que el modulo vuelva al modo de activo
    Serial1.end();
    Serial1.begin(57600);                             //Cambio de velocidad del UART a la velocidad de comunicacion maxima
    Serial.println("Configurado!!!");                 //Solo para depuracion
}
