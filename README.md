# sensorRuido
Código de sensor de ruido para Arduino UNO R3

A grandes rasgos el código inicializa los pines digitales de los LEDs, la pantalla LCD con su módulo I2C y al sensor KY-038, y luego mediante condicionales lógicos si-sino si-sino (if - else if - else en inglés) y acumuladores de acuerdo al tiempo de trabajo del sensor (contado en milisegundos, siendo 1000 milisegundos igual a 1 segundo)se define por comparación de máximos y mínimos un barrido o mapeo de dichos máximos y mínimos que ingresan directo al sensor, y de acuerdo a los valores promedio arrojados, estos se pueden asociar a un distinto color del LED, siendo verde el ruido normal a moderado (menor igual a 60 dB), amarillo el ruido moderado a alto (entre 60 - 85 dB), y rojo para el ruido alto a muy alto (mayor igual a 85 dB)

Cabe destacar que en el IDE de Arduino es posible saber que valores numéricos del ruido salen por la salida serial programada para el proyecto a 115200 baudios por lo que solo usando una computadora se puede ver el gráfico generado con los datos que recoge el sensor de ruido durante todo el tiempo, y como esto no es posible hacerlo solo confiándose de las luces LED, de ahí la importancia de usar una pantalla LCD para mostrar si bien no la gráfica de mapeo, si los valores de ruido en un determinado momento concreto.