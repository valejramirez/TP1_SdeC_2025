# Checklist de Tutorial de Profiling en Linux con `gprof` y `perf`

## Requerimientos e instalación de herramientas
- [ ] Instalar gcc, make y las herramientas de desarrollo:

    sudo apt update
    sudo apt install build-essential

- [ ] Instalar linux-tools (para perf):

    sudo apt install linux-tools-common
    sudo apt install linux-tools-$(uname -r)

- [ ] Instalar gprof2dot y graphviz (para la visualización de gprof):

    pip install gprof2dot
    sudo apt install graphviz

![Captura de pantalla 2025-03-29 104226](https://github.com/user-attachments/assets/25d792cc-923d-47cd-86b5-754e8826b6b2)

![Captura de pantalla 2025-03-29 104257](https://github.com/user-attachments/assets/a3012b4a-c9f1-490f-8d0d-51ae04b86462)

![Captura de pantalla 2025-03-29 104400](https://github.com/user-attachments/assets/fe28285f-50d4-4eff-b010-d82a01080cc1)

## Parte 1: Profiling con GPROF

### Preparación del código
- [ ] Crear archivo `test_gprof.c` con el siguiente contenido:

```c
#include <stdio.h>

void new_func1(void);

void func1(void) {
    printf("\n Inside func1 \n");
    for (int i = 0; i < 0xffffffff; i++);
    new_func1();
}

static void func2(void) {
    printf("\n Inside func2 \n");
    for (int i = 0; i < 0xffffffaa; i++);
}

int main(void) {
    printf("\n Inside main()\n");
    for (int i = 0; i < 0xffffff; i++);
    func1();
    func2();
    return 0;
}
```

- [ ] Crear archivo `test_gprof_new.c` con la siguiente función:

```c
#include <stdio.h>

void new_func1(void) {
    printf("\n Inside new_func1()\n");
    for (int i = 0; i < 0xffffffee; i++);
}
```
![Captura de pantalla 2025-03-29 104904](https://github.com/user-attachments/assets/d1be9d4b-8cd6-46b3-b289-0152d4d5fe73)

### Compilación con soporte de profiling
- [ ] Compilar usando:

    gcc -Wall -pg test_gprof.c test_gprof_new.c -o test_gprof

### Ejecución del programa
- [ ] Ejecutar:

    ./test_gprof

  Esto generará `gmon.out`.

![Captura de pantalla 2025-03-29 105017](https://github.com/user-attachments/assets/63953e0e-bd1d-4072-adc7-e9e8213ebc7b)

### Generar análisis de perfil
- [ ] Ejecutar:

    gprof test_gprof gmon.out > analysis.txt

- [ ] Verificar que el archivo `analysis.txt` contiene:
  - [ ] Flat profile
  - [ ] Call graph


![Captura de pantalla 2025-03-29 105115](https://github.com/user-attachments/assets/96752b56-aee5-487d-bae8-f31044b11298)

![Captura de pantalla 2025-03-29 105140](https://github.com/user-attachments/assets/f872b744-7eb1-40d0-83f4-ff3e0603b994)

### Personalización del análisis con flags (ejecutar cada uno y analizar)
- [ ] `gprof -a test_gprof gmon.out > analysis.txt`  
  - Suprime funciones `static` como `func2`
  - [ ] Verificar que `func2` no aparece en el output

- [ ] `gprof -b test_gprof gmon.out > analysis.txt`  
  - Elimina explicaciones detalladas

- [ ] `gprof -p -b test_gprof gmon.out > analysis.txt`  
  - Solo muestra perfil plano

- [ ] `gprof -pfunc1 -b test_gprof gmon.out > analysis.txt`  
  - Muestra solo datos de `func1`

![Captura de pantalla 2025-03-29 105925](https://github.com/user-attachments/assets/711e0f3c-b7d4-4d1d-96e6-fb1d09d140ee)

![Captura de pantalla 2025-03-29 110002](https://github.com/user-attachments/assets/ff8c1f6c-7523-46c9-b040-8cdc08ab4ee8)

![Captura de pantalla 2025-03-29 110046](https://github.com/user-attachments/assets/2a958f69-2243-4edc-9ce0-7e860e4e7dcb)

![Captura de pantalla 2025-03-29 110150](https://github.com/user-attachments/assets/748b5ef4-a3dc-4d00-8438-5b90784525a9)

### Visualización con gprof2dot
- [ ] Instalar herramientas necesarias:

    pip install gprof2dot

    sudo apt install graphviz

- [ ] Generar gráfico:

    gprof test_gprof gmon.out | gprof2dot | dot -Tpng -o output.png

- [ ] Verificar que se generó `output.png`

![Captura de pantalla 2025-03-29 110239](https://github.com/user-attachments/assets/1b6a816f-ac19-473e-ab40-175d667389d7)

![Captura de pantalla 2025-03-29 110411](https://github.com/user-attachments/assets/46b7500f-2e39-4175-af24-975556afb293)

## Parte 2: Profiling con `perf`


### Ejecución de análisis con `perf`
- [ ] Ejecutar:

    sudo perf record ./test_gprof

- [ ] Generar reporte interactivo:

    sudo perf report

![Captura de pantalla 2025-03-29 110548](https://github.com/user-attachments/assets/fb36f01b-c1c3-4f19-8244-d45cfa515e0f)

## Limpieza opcional
- [ ] Eliminar archivos generados si se desea:

    rm gmon.out test_gprof analysis.txt output.png

## Fin del tutorial
- [ ] Confirmar comprensión de:
  - [ ] Perfil plano
  - [ ] Gráfico de llamadas
  - [ ] Flags para personalización
  - [ ] Visualización con `gprof2dot`
  - [ ] Análisis básico con `perf`

![Captura de pantalla 2025-03-29 110648](https://github.com/user-attachments/assets/8c9bd661-1b9e-46b1-9a6a-becc776039ca)

