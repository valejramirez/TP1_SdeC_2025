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

[Aquí iría una imagen mostrando la instalación de todas las herramientas necesarias]


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

[Aquí iría una foto mostrando los archivos creados en el explorador de archivos o terminal]

### Compilación con soporte de profiling
- [ ] Compilar usando:

    gcc -Wall -pg test_gprof.c test_gprof_new.c -o test_gprof

[Aquí iría una foto mostrando el comando ejecutado y el binario generado]

### Ejecución del programa
- [ ] Ejecutar:

    ./test_gprof

  Esto generará `gmon.out`.

[Aquí iría una foto mostrando la ejecución del programa y el archivo `gmon.out` generado]

### Generar análisis de perfil
- [ ] Ejecutar:

    gprof test_gprof gmon.out > analysis.txt

- [ ] Verificar que el archivo `analysis.txt` contiene:
  - [ ] Flat profile
  - [ ] Call graph

[Aquí iría una captura del contenido de `analysis.txt` en un editor de texto o en terminal]

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

[Aquí iría una imagen comparativa entre varios `analysis.txt` generados con flags distintos]

### Visualización con gprof2dot
- [ ] Instalar herramientas necesarias:

    pip install gprof2dot

    sudo apt install graphviz

- [ ] Generar gráfico:

    gprof test_gprof gmon.out | gprof2dot | dot -Tpng -o output.png

- [ ] Verificar que se generó `output.png`

[Aquí iría una foto del gráfico generado con nodos y flechas representando las llamadas]

## Parte 2: Profiling con `perf`


### Ejecución de análisis con `perf`
- [ ] Ejecutar:

    sudo perf record ./test_gprof

- [ ] Generar reporte interactivo:

    sudo perf report

[Aquí iría una captura del reporte interactivo mostrando funciones más costosas]

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

[Aquí iría una imagen final mostrando una carpeta limpia y los resultados esperados]

