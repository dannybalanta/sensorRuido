#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Crear el objeto lcd  dirección  0x27F y 16 columnas x 2 filas

const int ventanaMuestra = 50; // Valor de muestreo en milisegundos, siendo (50 mS = 20Hz)
unsigned int muestra; // variable para definir el tamaño de la muestra para hacer el mapeo
 
#define lecturaAnaloga A0 // Pin A0 como de salida analógica
#define pinVerde 7 // pin 7 para luz led verde 
#define pinAmarillo 6 // pin 6 para luz amarilla
#define pinRojo 5 // pin 5 para luz roja
 
void setup () {   
  pinMode (lecturaAnaloga, INPUT); // Establece el pin A0 como de entrada al detectar sonido  
  pinMode(pinVerde, OUTPUT); // define el pin verde para salida
  pinMode(pinAmarillo, OUTPUT); // establece pin amarillo como pin de salida 
  pinMode(pinRojo, OUTPUT);  // establece el pin rojo como pin de salida
 
  digitalWrite(pinVerde, LOW); // pin verde apagado al iniciar
  digitalWrite(pinAmarillo, LOW); // pin amarillo apagado al iniciar
  digitalWrite(pinRojo, LOW); // pin rojo apagado al iniciar
  
  Serial.begin(115200); // inicializa puerto serial a 115200 baudios
  lcd.init(); // inicializa la pantalla LCD
 
  // Turn on the backlight.
  lcd.backlight(); // fija el contraste en la pantalla LCD
    lcd.clear(); // limpia la pantalla LCD
}  
 
   
void loop () { 
   unsigned long startMillis= millis();                   // inicio del muestreo
   float peakToPeak = 0;                                  // medida de los picos mínimo y máximo
 
   unsigned int signalMax = 0;                            // Valor mínimo de 0
   unsigned int signalMin = 1024;                         // Valor máximo de 1024
 
                                                          
   while (millis() - startMillis < ventanaMuestra) {   // mientras lee los datos cada 50 ms (milisegundos) 
   
      muestra = analogRead(lecturaAnaloga);                    // toma las lecturas del micrófono del sensor
      if (muestra < 1024) {                                  // elimina las lecturas parásitas
      
         if (muestra > signalMax) {  // si la muestra excede a la señal detectada
         
            signalMax = muestra;                           // almacene en la variable muestra la señal maxima
         }
		 
         else if (muestra < signalMin)  { // sino si la muestra es inferior a la señal detectada
         
            signalMin = muestra;                           // almacene en la variable muestra la señal mínima
         }
      }
   }
 
   peakToPeak = signalMax - signalMin;             // define la amplitud del pico como la resta de max - min
   int db = map(peakToPeak,20,900,49.5,90);      //convierte a decibeles las lecturas por medio del mapeo
 
  lcd.setCursor(0, 0); // fija el cursor en la primera linea
  lcd.print("Ruido: ");
  lcd.print(db);
  lcd.print("dB");
  
  if (db <= 60)  {  // si la cantidad de decibeles es inferior a 60
    lcd.setCursor(0, 1); // fija el cursor en la segunda linea
    lcd.print("Nivel: Normal"); // muestra que el nivel de ruido es Normal 
    digitalWrite(pinVerde, HIGH); // enciende el LED Verde y mantiene apagados el LED Rojo y Amarillo
    digitalWrite(pinAmarillo, LOW);
    digitalWrite(pinRojo, LOW);
  }
  
  else if (db > 60 && db<85)  { // sino si el nivel de ruido está entre mas de 60 dB hasta 85 dB entonces
    lcd.setCursor(0, 1); // fija el cursor en la segunda linea
    lcd.print("Nivel: Moderado"); // muestra que el nivel de ruido es Moderado
    digitalWrite(pinVerde, LOW); 
    digitalWrite(pinAmarillo, HIGH); // enciende el LED Amarillo y mantiene apagados el LED Verde y Rojo
    digitalWrite(pinRojo, LOW);
  }
  
  else if (db>=85)  { // sino si el nivel de ruido excede los 85 dB entonces
    lcd.setCursor(0, 1); // fija el cursor en la segunda linea
    lcd.print("Nivel: Alto"); // muestra que el nivel de ruido es Alto
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAmarillo, LOW);
    digitalWrite(pinRojo, HIGH); // enciende el LED Rojo y mantiene apagados el LED Verde y Amarillo
 
  }
   
   delay(200);  // tiempo de espera de 200 milisegundos entre cada medición
   lcd.clear(); // limpia la pantalla 
}
