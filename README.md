![image](https://github.com/user-attachments/assets/5fc7fee0-ce94-4bd0-9924-cd599687e0e8)

# Desarrollo de Software en Sistemas Distribuidos

## Autor
**Nahuel Flores**

## Actividad Sockets

### 1. Estructura del Proyecto

#### 1.1 Servidor

El servidor está desarrollado en C con el IDE Dev C++. Por lo tanto, la extensión del archivo para correr el servidor es `.dev` y se llama `sockets-server`.

El programa está orientado a estructuras, con las siguientes funciones:

##### 1.1.1 `configServerSocket`
Este método es el principal para levantar el socket.

##### 1.1.2 Métodos de ayuda

- **`isNumber`**: Valida que lo que se está ingresando es un número.
- **`deleteLineBreak`**: Elimina el salto de línea cuando se capturan datos.
- **`clearConsole`**: Vacía la consola.

##### 1.1.3 `generateUserName`
Este método se utilizó para resolver el punto uno del trabajo "Generador de nombre de usuario". Dependiendo de la longitud, generará el nombre correspondiente.

La estrategia utilizada para generar el usuario de forma aleatoria es usar dos cadenas: una que contiene solo letras sin vocales y otra solo vocales. Dependiendo de si el número aleatorio es 0 o 1, la primera será vocal o consonante. Se genera el nombre a partir de la cadena correspondiente con otro número aleatorio que va de 0 a 25 para elegir la letra al azar, y luego una vocal que va de 0 a 4 para elegirla. Este proceso se repite hasta completar el bucle.

##### 1.1.4 `generatePassword`
Similar al caso anterior, pero el uso está orientado al "Generador de contraseñas". La única diferencia es que se usa una cadena de caracteres alfanuméricos, y para darle mayor aleatoriedad, se mezclan los órdenes para agregar un pequeño grado de variabilidad adicional.

##### 1.1.5 Validaciones de casos de uso

- **`processMessageGeneratorUsername`**
- **`processMessageGeneratorPassword`**

Ambos métodos toman la respuesta del cliente y, dependiendo del caso de uso, llamarán a las funciones correspondientes o responderán con un error si la longitud no es la correcta.

##### 1.1.6 `mainProcess`
Dependiendo de la opción que elija el cliente (generar usuario o contraseña), responderá al usuario con la opción correspondiente.

##### 1.1.7 `mainGenerator`
Encargado de orquestar el proceso de crear usuario o contraseña.

##### 1.1.8 Librerías utilizadas
```c
#include <winsock2.h>   // Para los sockets.
#include <ctype.h>      // Para verificar si es un número dentro de un char.
#include <stdbool.h>    // Para poder generar booleanos.
#include <time.h>       // Para generar los números aleatorios.
```

## 2.1 Clientes

El primer cliente está desarrollado en C, como se especificó anteriormente, con la diferencia de que el IDE elegido fue Code::Blocks, por lo que su extensión corresponde a `.cbp`. El segundo cliente fue desarrollado en Java con el IDE Eclipse.

El primer cliente está orientado a estructuras, mientras que el cliente programado en Java está orientado a objetos con procedimientos.

### 2.1.2 Cliente en C - Métodos

- **`configClientSocket`**: Este método es el principal para levantar el socket.
- **`deleteLineBreak`**: Este método elimina el salto de línea cuando se capturan datos.
- **`clearConsole`**: Para vaciar la consola.
- **`mainMenu`**: Es el menú principal en donde el cliente elige qué quiere generar. A partir de su mensaje, se enviará un mensaje al servidor para continuar la comunicación hasta generar su usuario o contraseña dependiendo de su respuesta.

### 2.1.3 Cliente en Java - Métodos

- **Clase `MasterSocket`**: Es la encargada de enviar, mostrar y recibir mensajes del servidor, siendo la principal responsable de todo el flujo de mensajes.
- **`mainMenu`**: Es el menú principal en donde el cliente elige qué quiere generar. A partir de su mensaje, se enviará un mensaje al servidor para continuar la comunicación hasta generar su usuario o contraseña dependiendo de su respuesta.
- **`addLineBreak`**: Este método añade el salto de línea para mostrar datos.
- **`clearConsole`**: Para vaciar la consola.

## 3. Ciclo de Vida

### 3.1 Funcionamiento Correcto

![image](https://github.com/user-attachments/assets/2f606121-3cb1-4a29-a3d9-69bd51323f22)

### 3.2 Funcionamiento Incorrecto

![image](https://github.com/user-attachments/assets/a571c71c-b011-463a-9b4c-897531ee69e9)


## 4. Pruebas

### 4.1 Pruebas Cliente-Servidor

- **Servidor - Completo**

![image](https://github.com/user-attachments/assets/4e329441-7d0d-4036-8205-16c56196f22d)


### 4.2 Cliente en C

- **Generar Usuario - Correcto**

![image](https://github.com/user-attachments/assets/54d0ce90-59eb-4589-bd9c-2a55335d06a5)

- **Generar Usuario - Incorrecto**

![image](https://github.com/user-attachments/assets/93c48497-b72f-4f7b-b7d0-086901df44cc)

- **Generar Clave - Correcto**

![image](https://github.com/user-attachments/assets/8510ce99-2c77-4d10-ae38-d07d44867c22)

- **Generar Clave - Incorrecto**

![image](https://github.com/user-attachments/assets/19568037-a50c-4327-8eaa-2ae36f402fc0)

### 4.3 Cliente en Java

- **Generar Usuario - Correcto**

![image](https://github.com/user-attachments/assets/cda8b9be-c9b4-4a25-8416-d5a4283975c4)

- **Generar Usuario - Incorrecto**
  
![image](https://github.com/user-attachments/assets/99ad0c29-bfd6-487a-a740-7010625c6e82)

- **Generar Clave - Correcto**

![image](https://github.com/user-attachments/assets/a6e50472-8616-4c40-8221-1795e556c613)

- **Generar Clave - Incorrecto**

![image](https://github.com/user-attachments/assets/0a02a033-eef8-424e-8a9a-191ab079ca82)
