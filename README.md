# ESP32-Interrupciones
Manejo de interrupciones en ESP32

Se hace uso de un push button para manejar la interrupción y también se usan dos LEDs para mostrar la interrupción.
Primero se definen los GPIOs que seran usados
Se declara la función para el manejo de interrupciones

Se realiza la inicicalización de los GPIOs
  Usar la estructura gpio_config_t pararealizar la configuración
    Definición de primer GPIO para primer LED: se define como salida, se deshabilitan las interrupciones y las resistencias Pullup y Pulldown
    Definición de segundo GPIO para segundo LED: se define como entrada y salida (para poder obtener su estado más adelante), se deshabilitan las interrupciones y las resistencias Pullup y Pulldown
    Definición de tercer GPIO para el botón: se define como entrada, se habilitan las interrupciones, se deshabilita la resistencia Pulldown y se habilita la resistencia Pullup.

  Realizar la instalación del servicio de interrupciones
  Añadir el manejador de interrupciones para el PIN del botón

Declaración de variables para el manejo del estado de los LEDs

Definición de la función para manejo de interrupciones. Como se trata de una función para el manejo de Interrupciones esta debe ser colocada en la IRAM del procesador, por eso colocamos el atributo IRAM_ATTR en la definición de la función
  Dentro de la función de realzian dos operaciones sencillas.
    La primer es realizar el envío del estado de una variable declarada previamente (led_state), se manda el estado invertido.
    La segunda es más interesante aunque también sencilla, se obtiene el estado del segundo LED (gpio_get_level())  y se asigna a una variable, por último este estado se vuelve a mandar al LED pero de forma invertida.

Por último se tiene la función principal donde se mandamos llamar la función para inicializar los GPIOs y tenemos un siclo infinito dentro se encuentra un delay de un segundo para evitar falsos positivos con el botón (evitar reconocimeinto de rebotes)
