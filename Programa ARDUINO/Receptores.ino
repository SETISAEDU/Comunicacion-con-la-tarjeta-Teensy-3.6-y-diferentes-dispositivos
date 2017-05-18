//PROGRAMA SECUNDARIO//


const int SetPin = 2;                 //pin de configuracion para el APC220
const int LED1 = 5;                  // Pin designado para indicador LED (Recepor con modulo APC 220)
const int LED2 = 6;            
const int LED3 = 7;

char estado;
char estado2;

#define event_1 0x10                             //identificadores para la recepción  de datos a los dispositivos
#define event_2 0x20

bool apagar_led_bt=false, enceder_led_bt=false; //Banderas para el control de la secuencia de accion de los pulsadores
bool apagar_led2=false, enceder_led2=false;
bool apagar_led3=false, enceder_led3=false;


void setup() {
 Serial.begin(57600);                            //Solo para depuracion 
 Serial1.begin(57600);
 Serial2.begin(9600);
 Serial3.begin(9600);
 pinMode(SetPin, OUTPUT);                       //Configuracion de pin de control para el modulo como salida
 pinMode (LED1, OUTPUT);
 pinMode(LED2, OUTPUT);               
 pinMode(LED3, OUTPUT);  
 digitalWrite(SetPin, HIGH);                    //Inicializacion del pin de control SET en alto
 ConfigAPC();                                   //Configuracion del modulo APC 220
 
}

void loop() {
  
  int DataIn = Serial1.read();                 //Lectura del dato
  int ID = DataIn;                             // Recepción del indicador, enviado por los modulos APC 220
    
    if (ID == event_1)
    {
      digitalWrite(LED1, HIGH);
       
    }
    if (ID == event_2)
    {
      digitalWrite(LED1,LOW);
    }

  if (Serial2.available())
    {          
       estado = Serial2.read();               //Lectura de los datos disponibles en el puerto serial 2
     
      if (estado == 'A')          
      {
        // Enciendo el LED (nivel ALTO)
        digitalWrite(LED2, HIGH);        
      }
     
      if (estado == 'B')          
      {
        // Apago el LED (nivel BAJO)
        digitalWrite(LED2, LOW);        
      }
    }

    if (Serial3.available())                  //Lectura de los datos disponibles en el puerto serial 3
    {          
       estado2 = Serial3.read();  
     
      if (estado2 == 'C')          
      {
        // Enciendo el LED (nivel ALTO)
        digitalWrite(LED3, HIGH);        
      }
     
      if (estado2 == 'D')          
      {
        // Apago el LED (nivel BAJO)
        digitalWrite(LED3, LOW);        
      }
    }
}
//Funcion de configuracion del modulo APC220
void ConfigAPC() 
{
                                                        // Procedimiento de configuración a 450MHz
    Serial.println("Configurando a 450MHz ...");
    digitalWrite(SetPin, LOW);                          //Escritura en bajo del pin SET
    delay(2);                                           //Espera necesari antes de poder enviarle comandos
    Serial1.end();
    Serial1.begin(9600);                               //Cambio de velocidad del UART, a la velocidad de configuracion
    Serial1.println("WR 450000 4 9 6 0");               //Envio de datos de configuracion
    delay(201);                                         //Espera antes de la respuesta por parte del modulo

    if (Serial1.available())                             //Verificacion de que el modulo a contestado
    {
      String data = Serial1.readString();
      Serial.println(data);                              //Solo para depuracion
    }
    digitalWrite(SetPin, HIGH);                         //Restablecimiento del pin al valor de alto
      delay(11);                                       //Espera antes de que el modulo vuelva al modo de activo
    Serial1.end();
    Serial1.begin(57600);                               //Cambio de velocidad del UART a la velocidad de comunicacion maxima
    Serial.println("Configurado!!!");                   //Solo para depuracion
}
