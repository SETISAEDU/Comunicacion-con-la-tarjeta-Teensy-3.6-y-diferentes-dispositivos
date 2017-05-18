# Comunicacion-con-la-tarjeta-Teensy-3.6-y-diferentes-dispositivos

# Puertos seriales
La comunicación serial se lleva a cabo asincrónicamente, es decir que no es necesaria una señal (o reloj) de sincronización: los datos pueden enviarse en intervalos aleatorios. A su vez, el periférico debe poder distinguir los caracteres (un carácter tiene 8 bits de longitud) entre la sucesión de bits que se está enviando. 

La tarjeta de desarrollo Teensy 3.6 ofrece hasta seis puertos seriales. Las señales en serie de los pines Rx o Tx son niveles lógicos a 3.3 V.

##	Configurando los diferentes dispositivos.
Para lograr la comunicación serial de los diferentes dispositivos electrónicos con la tarjeta Teensy 3.6 es necesario considerar las siguientes configuraciones:

### Configurando los módulos RF APC 220
El siguiente código es dedicado a la configuración inicial para la comunicación serial con los módulos RF ACP 220
 
    Serial.println("Configurando a 450MHz ...");
    digitalWrite(SetPin, LOW); //Escritura en bajo del pin SET
    delay(2); //Espera necesaria antes de poder enviarle comandos
    Serial1.end();
    Serial1.begin(9600); //Cambio de velocidad del UART, a la velocidad de configuracion
    Serial1.println("WR 450000 4 9 6 0"); //Envio de datos de configuracion
    delay(201); //Espera antes de la respuesta por parte del modulo
    if (Serial1.available()) //Verificacion de que el modulo a contestado
    {
      String data = Serial1.readString();
      Serial.println(data);  //Solo para depuracion
    }
    digitalWrite(SetPin, HIGH); //Restablecimiento del pin al valor de alto
    delay(11); //Espera antes de que el modulo vuelva al modo de activo
    Serial1.end();
    Serial1.begin(57600); //Cambio de velocidad del UART a la velocidad de comunicacion maxima
    Serial.println("Configurado!!!"); //Solo para depuracion 

### Configurando los módulos bluetooth HC-05

En el código `modo_AT_B1.ino` se encuentra el programa dedicado a la configuración de todos los parámetros para que se pueda realizar una comunicación Bluetooth.

# Diagrama de conexión 
Conecte los diferentes dispositivos de comunicación serial y los elementos electrónicos como se muestra en el siguiente diagrama: 

![Diagrama](https://raw.githubusercontent.com/SETISAEDU/Comunicacion-con-la-tarjeta-Teensy-3.6-y-diferentes-dispositivos/master/Serial%20Teensy%203.6_bb.png)

# Programando

El programa principal que se cargara a la Teensy 3.6 es: `Serial_Teensy.ino` y el programa secundario que se cargara al ARDUINO Mega es: `Receptores`


