# _**G6: Juego de Autos**_

DOCUMENTO DE DISEÑO

### **(Grupo 5)**

ÍNDICE

<table>
  <tr>
    <td colspan = "2"> Resumen </td>
  </tr>
  <tr>
    <td> Géneros:   Videojuego de carreras </td>
    <td> Modos: 3 modos de juego: Velocidad de los coches baja, media y rápida </td>
  </tr>
  <tr>
    <td> Público objetivo: <br>
         Varones, 20 / 30 años, Europa <br>
         (Según las ventas de otros juegos de carreras como “Need for Speed” o “Gran Turismo”)    
    </td>
    <td> Plataformas: PC web</td>
  </tr>
  <tr>
    <td> Cantidades: <br><br>
         Escenarios : 1 circuito <br>
   </td>
    <td> Hitos: <br>
           Fecha de lanzamiento: 5 de mayo de 2023 <br>
   </td>
  </tr>
</table>



## Logotipo y portada del juego
 
 ![Logo_dark](https://user-images.githubusercontent.com/82372508/236561922-630de05f-6920-4402-89af-e35170230e1e.png)

## Tabla de contenidos
1. [Aspectos Generales](#aspectos-generales)  
    1.1 [Relato breve y parcial de una partida típica](#relato-breve)  
  
2. [Jugabilidad](#Jugabilidad)  
    2.1 [Mecánica](#Mecánica)   
         - [Mecánicas del personaje](#Mecánicas-personaje)  
         - [Mecánicas del enemigo](#Mecánicas-enemigo)  
    2.2 [Controles](#Controles) 
    2.3 [Cámara](#Camara) 
    2.4 [Dinámica](#Dinamica) 

3. [Estética](#Estetica)  
    3.1 [Menús y modos de juego](#Menus) 
    3.2 [Interfaz y control](#Interfaz)

4. [Breve descripción del sistema y plataforma de gestión](#Gestion)  
    4.1 [Breve descripción del sistema y plataforma de comunicación](#Comunicacion) 
 
5. [Contenido](#Contenido)  
    4.1 [Música](#Musica)  
    4.2 [Sonidos](#Sonidos)  
    4.3 [Assets gráficos](#Assets)  
    4.4 [Historia](#Historia)
    4.5 [Niveles](#Niveles)

6. [Referencias](#Referencias)

## <a name = "aspectos-generales">1. Aspectos generales</a>

![Captura de pantalla 2023-05-05 223757](https://user-images.githubusercontent.com/82372508/236564268-91b99a5a-0261-49bc-a07f-1435c6fb00fd.png)

### <a name = "relato-breve"> 1.1 Relato breve y parcial de una partida típica</a>

El jugador empieza en un menú principal en el cual puede interactuar con 2 botones clickables. El primero sirve para cambiar la velocidad de los coches (los cuales solo cambian la velocidad del gameplay, después mejor explicado). Cada vez que se pulsa se alterna entre las diferentes velocidades (100, 200 y 500 cc). El segundo botón sirve para comenzar la partida en la velocidad seleccionada.
Tras clickarlo, se pasará a la escena del circuito. Tanto el coche del jugador como de los rivales se situarán en la línea de salida (que también coincide con la meta). Los coches permanecerán inmóviles. Comenzará una cuenta atrás. El final de la misma servirá de señal de inicio de la carrera. Tras esto, los coches rivales comenzarán a moverse por la carretera, completando vueltas al circuito de manera automática. El coche del jugador pasará a ser controlable, comenzando la competición.
El jugador utilizará el botón de acelerar para que su coche se desplace hacia delante. Con los botones de giro, el jugador tendrá la opción de maniobrar su coche por las curvas. Si el jugador se sale del circuito en algún punto, caerá al vacío. Tras un lapso de tiempo, será respawneado en el último checkpoint que alcanzó, pudiendo así continuar la carrera.
Después de que el jugador complete tres vueltas al circuito, terminará la partida. En pantalla aparecerá la posición final en la que terminó el coche del jugador durante unos segundos.
Durante estos segundos, el jugador pierde el control del coche, el cual desacelerará hasta quedarse quieto.
Después de estos segundos, el jugador volverá a ver en pantalla el menú principal del juego.

## <a name = "Jugabilidad"> 2. Jugabilidad</a>
### <a name = "Mecánica"> 2.1 Mecánica</a>
####  <a name = "Mecánicas-personaje"> Mecánicas del personaje</a>
El personaje controlado por el jugador consta de un coche con las siguientes funcionalidades:

- Aceleración: hay un botón asignado para esta acción. Si este se mantiene presionado, la velocidad del coche aumenta según una variable predefinida hacia la parte frontal del coche. La velocidad del coche estará capada por un valor máximo constante.
Si el jugador dispone de un mando con gatillos adaptativos, la velocidad del coche dependerá de cuánto pulse estos. De esta manera, si pulsa el gatillo de aceleración a la mitad, la aceleración del coche será la mitad de la máxima. Si se pulsa completamente, la aceleración será máxima (equivalente a pulsar el botón del teclado de aceleración). 
Si el botón no está presionado, la velocidad actual del coche del jugador disminuirá, pues no se le aplicará ninguna aceleración. De este modo, el coche irá disminuyendo su velocidad hasta quedarse quieto.

- Giro: el jugador puede cambiar la dirección en la que mira el coche hacia los lados. De esta manera podrá controlar el giro del coche para maniobrar por la carretera.
Existen dos teclas asignadas a las direcciones en las que el coche puede girar: izquierda y derecha. Girando en torno a un pivote situado justo en medio del coche, en el eje Y (teniendo en cuenta Y representa la altura).
Cuando una de estas teclas se mantiene, el coche del jugador gira hacia esa dirección a velocidad angular constante, respetando una variable predefinida.
En el mismo momento en el que la tecla se deje de presionar, el coche dejará de girar y su velocidad angular será 0 instantáneamente.
En el caso de usarse el eje X de un Joystick, el coche girará en vez de a velocidad 1 como en el caso de la tecla del ordenador, girara dependiendo de la inclinación del joystick en cada momento, el cual devuelve un valor decimal entre 0 y 1.
Cuando el joystick se deja de inclinar y se queda en el medio, la velocidad angular del coche será 0 instantáneamente.
De esta manera, al girar, la parte frontal del coche cambia y por lo tanto cambia el destino del coche.

- Freno: una tecla será asignada para que cause el efecto contrario a la aceleración, es decir, frenar. Cuando esta tecla se mantiene presionada, la velocidad actual del coche disminuye teniendo en cuenta una variable predefinida. Si esta tecla se mantiene, la velocidad bajará hasta quedarse en 0, es decir, hasta que se pare el coche. Cuando el coche se haya frenado completamente, si seguimos pulsando esta tecla nos moveremos marcha atrás. La velocidad de marcha atrás es considerablemente inferior a la de hacia delante.

- Inclinación: cabe destacar que el circuito contiene varias partes en las que la carretera se inclina hacia un lado, llegando incluso hasta estar completamente girada. Cuando los coches pasan por estas zonas, se inclinarán para mantenerse paralelos a la carretera. De esta manera, la normal de la carretera será siempre paralela al eje Y del coche.
####  <a name = "Mecánicas-enemigo"> Mecánicas de enemigos</a>
Los enemigos son otros coches con la mismas habilidades que el coche controlado por el jugador, es decir, los enemigos pueden acelerar y girar de igual forma.
Comportamientos ya definidos en el apartado anterior.
La diferencia respecto al jugador es que estos coches estarán controlados por una IA, la cual tiene el mismo objetivo que el jugador, completar tres vueltas y terminar la carrera.

A lo largo de la carretera, se posicionarán unos llamados “Checkpoints”, los cuales tienen una doble funcionalidad:
- Por un lado sirven para detectar que el jugador sigue el trayecto creado y no se sale de ella.
- Por otro lado, sirven para que los coches rivales sepan a dónde ir en cada momento de la carretera.
Todos los coches rivales tendrán acceso a estos Checkpoints y su orden en la carretera.
Cuando empieza la carrera, cada coche rival sabrá cuál es el primer checkpoint y su posición en la carretera, por lo que acelerará y girará hasta que la parte frontal de su coche mire directamente hacia la posición de este.
Una vez que el coche detecta el checkpoint, buscará en su lista de checkpoints el siguiente siguiendo el orden de la carrera. Y así sucesivamente hasta completar tres vueltas.
En cuanto a su interacción con el jugador, los coches enemigos ignoran completamente al jugador y al resto de coches enemigos, su máxima prioridad es llegar al siguiente checkpoint.

El coche del jugador no podrá colisionar con los coches rivales (se atraviesan).

Los coches rivales también tendrán implementada la mecánica de inclinación según el punto de la carretera en el que estén.

### <a name = "Controles"> 2.2 Controles</a>
El juego podrá jugarse tanto desde el teclado como con un mando conectado al ordenador mediante un cable USB.
- Teclado: el jugador controla el coche con las teclas WASD

<table>
  <tr>
    <td colspan = "2"> Teclas </td>
  </tr>
  <tr>
    <td> W </td>
    <td> Aceleración </td>
  </tr>
  <tr>
    <td> S <br>  </td>
    <td> Freno/Marcha atrás </td>
  </tr>
  <tr>
   <tr>
    <td> A <br>  </td>
    <td> Girar a la izquierda </td>
  </tr>
 <tr>
    <td> D <br>  </td>
    <td> Girar a la derecha </td>
  </tr>
  </tr>
</table>

- Mando: el jugador controla el giro del coche con el joystick izquierdo, mientras que para la aceleración y freno cuenta con varias opciones. Podrá utilizar los hombros de ambos lados del mando, los gatillos y botones normales (por si el mando no dispone de los dos métodos anteriores).


<table>
  <tr>
    <td colspan = "2"> Mando </td>
  </tr>
  <tr>
    <td> Hombro derecho/Gatillo derecho/ Botón A (Xbox) o “Cruz” (PlayStation) </td>
    <td> Aceleración </td>
  </tr>
  <tr>
    <td> Hombro izquierdo/Gatillo izquierdo/ Botón B (Xbox) o “Círculo” (PlayStation) <br>  </td>
    <td> Freno/Marcha atrás </td>
  </tr>
  <tr>
   <tr>
    <td> Inclinar Joystick izquierdo a la izquierda <br>  </td>
    <td> Girar a la izquierda </td>
  </tr>
 <tr>
    <td> Inclinar Joystick izquierdo a la derecha <br>  </td>
    <td> Girar a la derecha </td>
  </tr>
  </tr>
</table>

- Giroscopio
El jugador podrá controlar el giro del coche haciendo uso del giroscopio de su mando (si dispone de él). En cualquier momento de la carrera, si se pulsa la flecha de arriba de la cruceta del mando, se alternará entre control con joystick o con giroscopio. Solo podrá estar activo simultáneamente uno de estos dos métodos de control, de manera que si se activa uno el otro es desactivado. 

### <a name = "Camara"> 2.3 Cámara</a>
La cámara tendrá el objetivo de seguir al coche desde su parte trasera.
Dicha cámara estará posicionada detrás del coche del jugador a una determinada altura de tal forma que el coche se puede observar en la parte inferior de la pantalla y en el medio se puede ver la carretera que tiene el coche delante, para que el jugador pueda ver a dónde se dirige en cada momento. La cámara no mira directamente al coche, si no a la dirección a la que está mirando la parte frontal del coche, de manera que el jugador verá la parte trasera del vehículo.
Cada vez que el coche se mueva o rote, la cámara lo seguirá de forma inmediata, sin delay.

### <a name = "Dinamica"> 2.4 Dinámica</a>
Objetivo: el objetivo principal del jugador consiste en terminar la carrera antes de que la termine cualquiera de los coches enemigos.
Para terminar la carrera, el jugador debe recorrer la carretera, la cual empieza justo donde termina, creando un ciclo infinito. La parte en la que empieza el jugador y el resto de coches es llamada meta. La carrera sólo se completará si el coche recorre la carretera y pasa por la meta tres veces.
Una vuelta a la carretera es completada al recorrer todos los checkpoints posicionados a lo largo de la misma.

- Ganar: el jugador cumplirá la condición de victoria del juego si consigue terminar la carrera habiendo dado 3 vueltas en primera posición, es decir antes de que cualquier otro coche consiga lo mismo.

- Perder: se considerará que el jugador ha perdido el juego cuando termina la carrera, pero después de que algún otro coche lo haya completado anteriormente, Es decir, el jugador no ha terminado la carrera en primera posición.
El coche no puede ser destruido ni se puede perder de otra forma.
No existe una pantalla de Game Over, el jugador solo sabe que ha perdido porque no ha quedado en primera posición. Por lo tanto, la carrera no terminará hasta que el jugador complete las tres vueltas, independientemente de si los coches rivales la han completado o no.

## <a name = "Estetica"> 3. Estética</a>

Se busca una estética inspirada principalmente en “F-Zero”. Coches con pocos polígonos y colores vivos.
Los coches, tanto del jugador como de los rivales, tendrán colores más saturados e interesantes para que destaquen más. El escenario consiste en una playa con colores cálidos y un circuito situado en ella.

### <a name = "Menus"> 3.1 Menús y modos de juego</a> 

Menú principal: 

El menú principal será lo primero que aparezca cuando se inicie el juego. 
Este es el único menú de todo el juego.
Consta de una imagen de fondo relacionada con la temática del juego. Encima de la misma se podrá leer el título del juego en la parte superior de la pantalla.
Debajo del título, existen dos botones ordenados verticalmente de la siguiente forma y con las siguientes funcionalidades:
- Cambiar dificultad: al pulsarlo, se alternará entre las 3 dificultades disponibles. El texto del botón indicará la dificultad seleccionada actualmente (100, 200 o 500 cc).
- Jugar: al presionar este botón, se iniciará la carrera.

### <a name = "Interfaz"> 3.2 Interfaz</a> 

La interfaz tendrá una complejidad baja. Constará de dos elementos base para el juego:
El número de vueltas que lleva el coche del jugador: en la esquina inferior izquierda, se mostrará un texto de forma X / Y, siendo X el número de vueltas que lleva el jugador y siendo Y el número de vueltas totales para terminar la carrera.
La posición en la que se encuentra el coche del jugador respecto al resto de coches enemigos:
En la esquina inferior derecha, se mostrará un texto de forma Xº, siendo X la posición actual del coche respecto al resto de coches enemigos.
Estas dos interfaces se irán actualizando automáticamente cada vez que sus respectivas variables cambien.
A esta interfaz base le hemos añadido los siguientes elementos:
Contador de velocidad: situado en la esquina superior izquierda. Tendrá el formato X km/h, siendo X la velocidad actual del jugador, en kilómetros por hora.
Contador de FPS: en la parte superior central.
Contadores de tiempo: situados en la esquina superior derecha, uno situado encima del otro. El superior contará el tiempo que lleva el jugador en la vuelta actual. Cuando se completa la vuelta al circuito, se resetea. El inferior mostrará el mejor tiempo del jugador en completar una vuelta, por lo que solo se actualizará cuando se complete una y en caso de que el tiempo empleado sea un nuevo record. 

## <a name = "Gestion"> 4. Breve descripción del sistema y plataforma de gestión</a>

Utilizaremos GitHub Issues como sistema de gestión, cada historia de usuario se escribirá como una issue y los responsables se la asignan como participante.
En la zona de descripción se proporcionará una breve descripción del funcionamiento intencionado, y algún consejo o recordatorio importante a tener en cuenta a la hora de la implementación, si fuese necesario.

### <a name = "Comunicacion"> 4.1 Breve descripción del sistema y plataforma de comunicación</a> 
Para mantener la comunicación del proyecto se utilizará la plataforma "Discord".
Se utilizarán canales de texto para concretar las horas de las reuniones, compartir código u otros recursos relevantes.
También se hará uso de los canales de voz para realizar las reuniones no presenciales en el canal general, y varios subcanales de voz en caso de que nos dividamos en grupos para determinadas tareas.
Para realizar y guardar el documento de diseño, el estilo de código, las presentaciones de los Hitos y elementos con mayor peso, se hará uso de una carpeta de Google Drive compartida a todos los miembros del grupo.

## <a name = "Contenido"> 5. Contenido</a>

### <a name = "Musica"> 5.1 Música</a> 
- Música menú
- Música gameplay

### <a name = "Sonidos"> 5.2 Sonidos</a> 
- Coche del jugador: aceleración 
- UI: Presionar botón y Cuenta atrás al inicio de la carrera
- Gameplay: Sonido al completar una vuelta y Sonido al llegar a la meta

### <a name = "Assets"> 5.3 Assets gráficos</a> 
- Personaje principal: Modelo 3D de un coche, con sus respectivas texturas.
- Enemigos: Modelo 3D de otro tipo de coche, con sus respectivas texturas.
- Escenario: Modelo 3D de una meta, con sus respectivas texturas.
- Carretera (creada con los splines de Ogre)

### <a name = "Historia"> 5.4 Historia</a> 
Llegabas tarde a las ofertas limitadas del Mercadona, pillaste el coche y “accidentalmente” acabaste en una competición para llegar el primero y conseguir los productos a mejor precio antes que los demás.


### <a name = "Niveles"> 5.5 Niveles</a> 
El juego consta de un único nivel jugable, el cual consta de una carretera en bucle (que inicia y termina en la meta).
El mismo nivel se jugará para los tres modos de juego, la única diferencia será la velocidad máxima de los coches.

## <a name = "Referencias"> 6. Referencias</a>
Estética basada en “Star Fox”, Pat McHale.
F-Zero, Nintendo, Shigeru Miyamoto
The Need for Speed, Electronic Arts
Gran Turismo, Polyphony Digital

