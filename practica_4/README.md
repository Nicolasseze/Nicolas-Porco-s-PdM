# Práctica 4 - MEF Anti-Rebote en STM32 Nucleo-F446RE

## Objetivo

Implementar una Máquina de Estados Finitos (MEF) para realizar anti-rebote por software, detectando flancos ascendentes y descendentes del pulsador de la placa NUCLEO-F4 y ejecutando acciones asociadas. Se utilizarán retardos no bloqueantes.

---

## Punto 1: Implementación básica en `main.c`

1. Crear un nuevo proyecto como copia del proyecto de la Práctica 3.

2. Implementar una MEF con los siguientes estados:
```c
typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
} debounceState_t;
```

3. El estado inicial de la MEF debe ser `BUTTON_UP`.

4. Las siguientes funciones deben implementarse en `main.c`:

```c
void debounceFSM_init();     // Inicializa la MEF
void debounceFSM_update();   // Actualiza el estado de la MEF (leer entradas, lógica de transición y salidas)
void buttonPressed();        // Encender el LED
void buttonReleased();       // Apagar el LED
```

5. El tiempo de anti-rebote debe ser de **40 ms** usando retardos **no bloqueantes**.

6. `debounceFSM_update()` debe llamarse periódicamente.

---

## Punto 2: Modularización del código

### Estructura del Proyecto
```
/drivers
  └── /API
      ├── /inc
      │   └── API_debounce.h
      └── /src
          └── API_debounce.c
```

### En `API_debounce.h`:
- Declaraciones públicas:

```c
void debounceFSM_init();
void debounceFSM_update();
bool_t readKey(); // Retorna true si hubo flanco descendente. Luego pone false.
```

---

### En `API_debounce.c`:

- Declaraciones y variables privadas:
  - Estado actual (tipo `debounceState_t`) declarado como `static`.
  - Variable booleana `static bool_t keyPressed` para detectar flanco descendente.

- Implementar:
  - MEF completa con temporización no bloqueante (40 ms).
  - Manejo de flanco descendente al pasar de `BUTTON_FALLING` a `BUTTON_DOWN`.

---

## Comportamiento del Programa Principal

- El LED debe cambiar su frecuencia de parpadeo entre **100 ms y 500 ms** cada vez que se presione el botón.
- Usar `readKey()` para detectar presiones reales.
- Usar el módulo de `delay` no bloqueante (`API_delay`) para manejar el parpadeo.

---

## Preguntas para Reflexionar

- ¿Se validan adecuadamente los parámetros pasados por el usuario?
- ¿Se notan mejoras en la detección de pulsaciones respecto a la Práctica 0?
- ¿Se pierden pulsaciones o hay falsos positivos?
- ¿Cada cuánto se llama a `debounceFSM_update()` y `readKey()`? ¿Qué ocurre si se llama con una frecuencia demasiado alta o baja?

---

## Requisitos

- STM32 Nucleo-F446RE
- STM32CubeIDE
- API de delay implementada en prácticas anteriores

---

## Créditos

Posgrado en Sistemas Embebidos - Programación de Microcontroladores  
Práctica 4 – Anti-rebote con MEF y diseño modular
