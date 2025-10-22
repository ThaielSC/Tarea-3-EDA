# Tarea 3: Calculadora Interactiva

Este proyecto es una implementación de una calculadora interactiva para la línea de comandos como.

La calculadora, llamada `EdaCal`, procesa expresiones aritméticas en **notación infija**, permite la asignación de variables y la visualización de la expresión en notación prefija, postfija y como árbol de expresión.

## TODO:

-   [ ] **Lexer:** Implementar el lexer para tokenizar la cadena de entrada (expresión infija).
-   [ ] **Parser (Infix a Postfix):** Implementar el algoritmo Shunting-yard para convertir la expresión de notación infija a postfija.
-   [ ] **Evaluación Postfix:** Evaluar la expresión en notación postfija para obtener el resultado.
-   [ ] **Soporte de Operaciones:**
    -   [ ] Suma (`+`), Resta (`-`), Multiplicación (`*`), División (`/`).
    -   [ ] Potenciación (`^`) y Radicación (`sqrt`).
-   [ ] **Árbol de Expresión:**
    -   [ ] Construir el árbol de expresión a partir de la notación postfija.
    -   [ ] Implementar el comando `tree` para mostrar el árbol.
-   [ ] **Notaciones:**
    -   [ ] Implementar el comando `posfix` para mostrar la notación postfija.
    -   [ ] Implementar el comando `prefix` para mostrar la notación prefija.
-   [ ] **Manejo de Variables:**
    -   [ ] Implementar la asignación de variables (`<nombre> = <expresion>`).
    -   [ ] Guardar el último resultado en la variable `ans`.
    -   [ ] Implementar el comando `show <variable>`.
-   [ ] **Aplicación Principal:**
    -   [ ] Crear el bucle interactivo con el prompt `>>`.
    -   [ ] Implementar el comando `exit` para terminar el programa.

## Comandos del Makefile

El `Makefile` automatiza la compilación y ejecución del proyecto.

*   **`make` o `make all`**: Compila el proyecto y crea el ejecutable en `build/main`.
*   **`make run`**: Ejecuta el programa. Si es necesario, lo compila primero.
*   **`make clean`**: Elimina todos los archivos generados por la compilación.
