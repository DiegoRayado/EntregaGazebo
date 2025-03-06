# EntregaGazebo
## Tabla de Contenidos
1. [Introducción](#Introduccion)
2. [Pioneer](#Pioneer)
3. [Controlador](#Controlador)
4. [Lanzar el programa](#i4)
## Introducción <a name="Introduccion"></a>
Tal y como se meciona en el guión se genera un laberinto de tamaño 10x12 (Según mi nombre) utilizando la herramienta proporcionada. El mapa es el siguiente:

![Captura](images/mapa.png)

Se posicion el robot pionner en el inicio (10.5,8.5). Por lo que se determina que el punto final se encuentra en la coordenada (1.5,1.5) ya que es la esquina opuesta. Se edita el suelo para añadirle un color azul mas vistoso.

## Pioneer <a name="Pioneer"></a>

### Cambios en el modelo 

Se añade un sensor, utilizando el codigo propocionado, pero se cambia el angulo de vision y el alcance del mismo.  

![Captura](images/sensor_add.png)

Se añade un gps, el cual se utiliza con el fin de indicar al robot cunado ha llegado a meta para poder detenerse e imprimirlo por pantalla. 

![Captura](images/gps_add.png)

## Controlador <a name="Controlador"></a>
### Video
[Enlace](https://youtu.be/X8nPELdxMe0)
### Descripcion
El controlador usa una logica muy simple, hace avanzar al robot hasta encontrar una pared. Cundo se topa con una pared realiza un giro de 90 grados y sigue avanzando (sino se topa con ninguna pared de nuevo). Finalmente se añade la detencion del robot cuando llega a meta. Como podemos observar es un controlador muy simple que no podria resolver ciertos mapas. Sin embargo, esto podría corregirse añadiendo un componente de aleatoriedad a los grados que gira y la direccion del giro. 

## Lanzar el programa <a name="i4"></a>
Importante en la carpeta buiild ejecutar:
<pre><code>cmake .. </code></pre>
<pre><code>make .. </code></pre>
Para lanzar el mundo de Gazebo con el modelo Pioneer, simplemente ejecuta el siguiente script:

<pre><code>./launch.sh</code></pre>

Este script realizará dos tareas principales:

1. Configurará automáticamente el `GAZEBO_MODEL_PATH` mediante el script de Python `set_gazebo_path.py`, que apunta a la carpeta de modelos.
2. Lanzará Gazebo con el archivo `map.world.xml` (mundo de Gazebo) que se encuentra en la carpeta `mundos`.

### 
Algoritmo de seguimiento de paredes: Su lógica es más sencilla y se puede mejorar fácilmente para reducir colisiones innecesarias contra las paredes. Sin embargo, este tipo de enfoques presentan el riesgo de quedar atrapados en bucles, girando alrededor de "islas" dentro del laberinto sin encontrar la solución.

