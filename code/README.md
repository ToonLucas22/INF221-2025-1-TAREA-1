# Documentación
(Nota: Esto sólo ha sido probado en Linux Mint 22)

## Multiplicación de matrices

### Programa principal
Para compilar y correr el programa principal, se debe invocar la terminal desde la carpeta de /matrix_multiplication/ y escribir los siguientes comandos:

  make
  make run

Una vez hecho esto, se empezarán a correr ambos algoritmos de multiplicación, sus output serán guardados en /matrix_multiplication/data/matrix_output/ y sus mediciones de ejecución en /matrix_multiplication/data/measurements/.

### Scripts
Una vez corridos los experimentos, el script de Python para generar los plots se llama plot_generator.py y se ubica dentro de /matrix_multiplication/scripts/. Al correrlo, se generarán los plots de medición de tiempo de los algoritmos naive y Strassen y se guardarán en la carpeta /matrix_multiplication/data/plots/.

Además, en caso de ser necesario regenerar los input, se pueden regenerar las matrices corriendo el script de matrix_generator.py ubicado en /matrix_multiplication/scripts/; las matrices generadas serán guardadas en /matrix_multiplication/data/matrix_input/.

## Ordenamiento de arreglo unidimensional

### Programa principal
Para compilar y correr el programa principal, se debe invocar la terminal desde la carpeta de /matrix_multiplication/ y escribir los siguientes comandos:

  make
  make run

Una vez hecho esto, se empezarán a correr los cuatro algoritmos de ordenamiento, sus output serán guardados en /sorting/data/array_output/ y sus mediciones de ejecución en /sorting/data/measurements/.

### Scripts
Una vez corridos los experimentos, el script de Python para generar los plots se llama plot_generator.py y se ubica dentro de /sorting/scripts/. Al correrlo, se generarán los plots de medición de tiempo de los algoritmos SelectionSort, MergeSort, QuickSort y std::sort y se guardarán en la carpeta /sorting/data/plots/.

Además, en caso de ser necesario regenerar los input, se pueden regenerar los arreglos corriendo el script de matrix_generator.py ubicado en /sorting/scripts/; los arreglos generados serán guardados en /sorting/data/array_input/.
