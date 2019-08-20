# Memory API # 

[![Developed by @santiago-b9826](https://img.shields.io/badge/developed%20by-%40SantiagoBedoya-blue.svg  "Santiago Bedoya")](https://github.com/santiago-b9826)   [![Developed by @linamariaum](https://img.shields.io/badge/developed%20by-%40linamariaum-ff69b4.svg  "Lina María Uribe")](https://github.com/linamariaum)

En este laboratorio ganará algún grado de familiaridad con la asignación de memoria (memory allocation). Para el caso, usted escribirá algunos programas con bugs. Luego, usará algunas herramientas para localizar los bugs que usted ha insertado. De este modo se familiarizará con algunas de estas herramientas para un uso futuro. Estas herramientas son: el debuger (**gdb**) y el memory-bug detector (**valgrind**).

## Questions ##

1. Escriba un programa simple llamado ```null.c``` que cree un puntero a un entero, llevelo a null y entonces intente desreferenciarlo (esto es, asignarle un valor). Compile este programa llamado ```null```. ¿Qué pasa cuando usted ejecuta este programa?

    > Al ejecutar este programa se obtiene en consola un ```Segmentation fault (core dumped)```, lo cual nos indica un error de acceso a memoria, ya que se declaró un apuntador y no se le indicó a qué dirección referenciar.
    ![Salida de la consola al ejecutar el programa: null.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/1.png)

2. Compile el programa del ejercicio anterior usando información de simbolos (con la flag -g). Al hacer esto se esta poniendo mas informacion en el ejecutable para permitir al debugger acceder a informacion util sobre los nombres de las variables y cosas similares. Ejecute el programa bajo el debugger digitando en consola (para el caso) ```gdb null``` y entonces una vez el ```gdb``` este corriendo ejecute ```run```. ¿Qué muestra gdb?

    > Lo que nos indica el ***debugger*** es que el error ```Segmentation fault``` se genera en la linea 5, al realizar la asignación del apuntador **p**, el cual previamente no referencia a ninguna dirección en memoria.
    ![Salida de la consola al ejecutar el programa con gdb: null.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/2.png)

3. Haga uso de la herramienta ```valgrind``` en el programa empleado en los puntos anteriores. Se usará la herramienta ```memcheck``` que es parte de ```valgrind``` para analizar lo que pasa: ``` valgrind --leak-check=yes null```. ¿Qué pasa cuando corre esto?, ¿Puede usted interpretar la salida de la herramienta anterior?

    > Al utilizar la herramienta ```memcheck``` que es un detector de errores de memoria y que es parte de ```valgrind```, nos indica que en la línea 5 del programa ```null.c``` no se reservo espacio de memoria para luego poder almacenar el valor correspondiente a un entero; por lo cual el proceso termina con la señal 11: el acceso no se encuentra dentro de la región asignada en la dirección 0x0. ```Segmentation fault```, el resultado de esto es un overflow en la región stack del programa.
    Con esta herramienta también podemos ver el espacio total usado por la región ***Heap***
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: null.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/3.png)

4. Escriba un programa sencillo que asigne memoria usando ```malloc()``` pero olvide liberarla antes de que el programa termine. ¿Qué pasa cuando este programa se ejecuta?, ¿Puede usted usar gdb para encontrar problemas como este?, ¿Que dice acerca de Valgrind (de nuevo use este con la bandera ```--leak check=yes```)?

    > Al ejecutar el programa llamado ```4.c```, vemos una ejecución sin problemas, imprimiendo en pantalla lo esperado.
    ![Salida de la consola al ejecutar el programa: 4.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/4.1.png)

    > Al utilizar ***gdb***,  vemos una ejecución sin problemas, imprimiendo en pantalla lo esperado e indicando que el programa finalizó de manera normal.
    ![Salida de la consola al ejecutar el programa con gdb: 4.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/4.2.png)

    > Al utilizar ***valgrind***, al parecer es más detallado y nos indica que se reservó un bloque de 40 bytes y que no fue liberado, es decir, ```definitely lost```.
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: 4.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/4.3.png)

5. Escriba un programa que cree un array de enteros llamado data de un tamaño de 100 usando ```malloc```; entonces, lleve el ```data[100]``` a ```0```. ¿Qué pasa cuando este programa se ejecuta?, ¿Qué pasa cuando se corre el programa usando ```valgrind```?, ¿El programa es correcto?

    > Al ejecutar el programa llamado ```5.c```, vemos una ejecución sin problemas, imprimiendo ***0*** en pantalla, aunque este no era el valor esperado.
    ![Salida de la consola al ejecutar el programa: 5.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/5.1.png)
    
    > Al utilizar ***valgrind***, se detectaron 2 errores, correspondientes a las lineas 7 y 8. El primero fue un error de escritura debido a que la posición 100 está fuera del rango del heap reservado. El segundo es un error de lectura al tratar de acceder a esta misma posición. Aún con estos errores detectados, el programa finalizó e imprimió ***0*** en la consola.
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: 5.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/5.2.png)

    > Consideramos que el programa no es correcto debido a que se accede a una posición ilegal y luego imprime un valor asignado a esa posición fuera de rango.

6. Codifique un programa que asigne un array de enteros (como arriba), luego lo libere, y entonces intente imprimir el valor de un elemento del array. ¿El programa corre?, ¿Que pasa cuando hace uso de ```valgrind```?

    > Si, el programa se ejecuta con normalidad.
    ![Salida de la consola al ejecutar el programa: 6.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/6.1.png)

    > Al utilizar ***valgrind***, se detecta un error generado en la línea 9 de este programa, en la cual se hace el proceso de lectura de un elemento del array que ha sido previamente liberado.
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: 6.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/6.2.png)

7. Ahora pase un **funny value** para liberar (e.g. un puntero en la mitad del array que usted ha asignado) ¿Qué pasa?, ¿Ústed necesita herramientas para encontrar este tipo de problemas?

    > Al ejecutar este programa, sale en pantalla un error indicando un puntero inválido.
    ![Salida de la consola al ejecutar el programa: 7.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/7.1.png)

    > Al utilizar ***valgrind***, se detectan 6 errores, los cuales son generados por el apuntador inválido, pudimos darnos cuenta de este tipo de error aún sin utilizar esta herramienta.
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: 7.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/7.2.1.png)
    ![Salida de la consola al ejecutar el programa con memcheck de valgrind: 7.c](https://raw.githubusercontent.com/linamariaum/memory-api/master/assets/7.2.2.png)

### Valgrind ###

1. http://valgrind.org/docs/manual/quick-start.html
2. http://www.st.ewi.tudelft.nl/koen/ti2725-c/valgrind.pdf
3. http://pages.cs.wisc.edu/~bart/537/valgrind.html
4. http://web.mit.edu/amcp/drg/valgrind-howto.pdf

### GDB ###

1. http://www.lsi.us.es/~javierj/ssoo_ficheros/GuiaGDB.htm
2. https://www.gdb-tutorial.net/
3. https://web.eecs.umich.edu/~sugih/pointers/summary.html
4. https://www.cs.umd.edu/~srhuang/teaching/cmsc212/gdb-tutorial-handout.pdf
5. https://lihuen.linti.unlp.edu.ar/index.php/C%C3%B3mo_usar_GDB
6. https://www.cs.cmu.edu/~gilpin/tutorial/
7. http://pages.di.unipi.it/bodei/CORSO_FP_17/FP/Lezioni/gdb-commands.pdf
8. https://cs.brown.edu/courses/cs033/docs/guides/gdb.pdf
9. https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf
10. http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf