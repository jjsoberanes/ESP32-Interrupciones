#include <stdio.h>
#include <stddef.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <esp_err.h> // Para utilizar los códigos de error ESP-IDF

// Definición de pines
#define LED_PIN 2
#define LED_PIN2 5
#define BUTTON_PIN 4

// Declaración de la función para manejo de interrupciones
static void buttonOne_handler(void *arg);

// Inicialización de GPIO
static void init_gpio()
{
    gpio_config_t io_config;

    // Configuración de PIN como salida para el LED
    io_config.intr_type = GPIO_INTR_DISABLE; // Configurar interrupción como deshabilitada
    io_config.mode = GPIO_MODE_OUTPUT; // Configurar como salida
    io_config.pin_bit_mask = (1ULL << LED_PIN); // Asignar el PIN a usar para el LED
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE; // Deshabilitar la resistencia PULLDOWN
    io_config.pull_up_en = GPIO_PULLUP_DISABLE; // Deshabilitar la resistencia PULLUP
    gpio_config(&io_config);

    //Configuración de PIN para salida LED2
    io_config.intr_type = GPIO_INTR_DISABLE;
    io_config.mode = GPIO_MODE_INPUT_OUTPUT;
    io_config.pin_bit_mask = (1ULL << LED_PIN2);
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&io_config);

    // Configurar PIN de entrada con interrupción en flanco descendente
    io_config.intr_type = GPIO_INTR_NEGEDGE;
    io_config.mode = GPIO_MODE_INPUT;
    io_config.pin_bit_mask = (1ULL << BUTTON_PIN);
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_config);

    // Instalar el servicio de interrupciones GPIO y verificar errores
    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK) {
        printf("Error instalando el servicio de interrupciones: %s\n", esp_err_to_name(err));
        return; // Salir si hay un error
    } else {
        printf("Servicio de interrupciones instalado correctamente.\n");
    }

    // Añadir el manejador de interrupciones para el pin del botón y verificar errores
    err = gpio_isr_handler_add(BUTTON_PIN, buttonOne_handler, NULL);
    if (err != ESP_OK) {
        printf("Error añadiendo el manejador de interrupciones: %s\n", esp_err_to_name(err));
    } else {
        printf("Manejador de interrupciones añadido correctamente.\n");
    }
}

// Definición de la función para manejo de interrupciones

static bool led_state = false;
static int stateLED_Input = 0;
static void IRAM_ATTR buttonOne_handler(void *arg)
{
    // Leer el estado actual del LED y cambiarlo
    led_state = !led_state; //gpio_get_level(LED_PIN);

    gpio_set_level(LED_PIN, led_state);

    stateLED_Input = gpio_get_level(LED_PIN2);

    gpio_set_level(LED_PIN2, !stateLED_Input);
    // Mensaje de depuración
    //printf("Interrupción manejada, estado del LED: %d\n", led_state);

    //printf("Estado del LED como Entrada: %d\n", stateLED_Input);

}

void app_main()
{
    // Inicialización de GPIO
    printf("Inicializando GPIO...\n");
    init_gpio();
    printf("GPIO inicializado.\n");

    // Bucle principal
    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Retraso de un segundo
        printf("Ejecutando bucle principal...\n");
    }
    vTaskSuspend(NULL);
}
