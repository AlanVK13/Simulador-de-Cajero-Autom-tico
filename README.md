# 🏧 Simulador de Cajero Automático en C++

Este es un proyecto de consola que simula las operaciones básicas de un cajero automático. Fue creado como una actividad académica para la materia de Programación Dinámica, implementando conceptos clave del lenguaje C++.

## ⚙️ Características Principales

El simulador permite a un usuario:
* **Iniciar Sesión:** Validar un número de cuenta y un PIN.
* **Consultar Saldo:** Ver el balance actual de la cuenta.
* **Depositar:** Añadir fondos a la cuenta.
* **Retirar:** Sacar fondos, validando que el saldo sea suficiente.
* **Transferir:** Enviar dinero a otra cuenta dentro del mismo banco (simulado).

## 🚀 Requisitos del Proyecto Implementados

Este proyecto cumple con los requisitos solicitados, utilizando diversos elementos del lenguaje C++:

* **Tipos de Datos:** Se utilizan `string`, `int`, `double` y `const`.
* **Estructuras (`struct`):** Se usa una `struct Account` para modelar y agrupar los datos de cada cuenta (número, titular, saldo, PIN).
* **Funciones:** El código está modularizado; cada operación (login, depósito, retiro, etc.) es una función independiente.
* **Arreglos:** Se utiliza un arreglo de `struct Account` para almacenar la base de datos simulada de las 3 cuentas.
* **Punteros:** Se usan punteros (ej. `Account*`) para modificar la información de la cuenta original del usuario logueado y evitar crear copias innecesarias.
* **Excepciones (`try-catch`):** Se implementa manejo de excepciones para validar las entradas de montos, asegurando que el usuario ingrese un número válido y no texto (ej. "abc").
* **Control de Flujo:**
    * **Selección:** `switch` para el menú principal e `if-else` para validaciones.
    * **Repetición:** `do-while` para el ciclo del menú principal y `while` para la validación de login y montos.


## 🧪 Datos de Prueba

Para probar el sistema, puedes usar las siguientes cuentas pre-cargadas:

| Titular | N° de Cuenta | PIN |
| :--- | :--- | :--- |
| Juan Perez | `12345` | `1111` |
| Maria Lopez | `67890` | `2222` |
| Carlos Sanchez | `11223` | `3333` |
