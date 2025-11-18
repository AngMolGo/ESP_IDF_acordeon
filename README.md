# ESP_IDF_acordeon

Este repositorio contiene una plantilla para un proyecto en ESP-IDF. Contiene ejemplos y librerías personales para desarrollar aplicaciones ágilmente en ESP32.

TODO:
- [ ] Configurar correctamente extensión de IDF.
- [ ] Configurar correctamente devcontainer para posicionar workspace solamente en /root.

## Estructura

El repositorio principalmente es un ejemplo básico de cómo se estructura un espacio de trabajo de programación con IDF, el SDK (Software Development Kit) oficial de Espressif, para programar sus microcontroladores.

Un workspace típico de IDF está conformado de la siguiente manera:

```
esp_ws 
├── build/
├── CMakeLists.txt
├── components/
├── main/
│   ├── CMakeLists.txt
│   └── main.c
└── sdkconfig
```

#### ```main/```

Es el directorio donde se almacena el código principal de la aplicación, funcionando como un workspace "básico" de una aplicación en lenguaje ```C```. Como es común, el código principal se programa en el archivo ```main.c```. 

En este directorio se puede incluir un directorio ```include``` para dividir el código en archivos ```.c``` y ```.h```.

#### ```CMakeLists.txt```

Son los archivos que contienen las instrucciones y directivas escritas en el lenguaje de CMake que describen cómo compilar el código fuente, encontrar bibliotecas, configurar opciones del compilador y del enlazador, y dónde instalar los resultados (ejecutables o bibliotecas), permitiendo la construcción de software.

Como se puede observar, existen dos archivos ```CMakeLists.txt``` en el workspace. El archivo ubicado en la raíz del espacio de trabajo es el archivo principal, el que le gestiona la compilación de toda la aplicación. El archivo ubicado en el directorio ```main``` se centra en definir los _archivos fuente_ principales, o sea, aquellos aquellos archivos ```.c``` que el código ```main.c``` utiliza y depende, y dónde se encuentran dichos archivos. Por lo que cada vez que se agregue un nuevo archivo o dependencia al código, se debe declarar en dicho archivo.

#### ```build/```

Es aquel directorio del workspace donde se almacenan los archivos generados durante el proceso de compilación del proyecto, es el lugar donde reside el "producto final" listo para ser flasheado y ejecutado.

#### ```sdkconfig```

El archivo ```sdkconfig``` contiene todas las opciones de configuración del proyecto generadas por la herramienta interactiva menuconfig de IDF. Este archivo define parámetros como:

- Configuración del microcontrolador (frecuencia de CPU, modos de arranque).

- Habilitación o deshabilitación de componentes del SDK.

- Ajustes de red (WiFi, Bluetooth, TCP/IP).

- Configuración de logs.

- Opciones de memoria y particiones.

- Ajustes específicos del proyecto, si los componentes los exponen.

- Entre muchos otros.

Aunque es un archivo de texto, no se edita manualmente. En su lugar, se modifica a través del comando:

``` bash
idf.py menuconfig
```

Luego IDF regenerará el ```sdkconfig``` con los valores seleccionados.

#### ```components/```

El directorio components/ contiene módulos de software reutilizables que amplían la funcionalidad del proyecto. En ESP-IDF, un componente es una unidad lógica de código que puede incluir archivos .c, .h, bibliotecas precompiladas, archivos de configuración y su propio CMakeLists.txt.

> [!IMPORTANT]
> Para utilizar componentes se debe especificar en el archivo principal ```CMakeLists.txt``` la siguiente definición:
> ``` CMakeLists.txt
> set(COMPONENTS_DIR "components")
> ```

Los componentes permiten organizar el proyecto en partes independientes y reutilizables, de forma que el código sea más modular y escalable. Cada componente puede tener dependencias propias, que se resuelven automáticamente gracias al sistema de build de CMake integrado en IDF.

Una estructura típica de un componente es:

``` bash
components/
└── mi_componente/
    ├── CMakeLists.txt
    ├── include/
    │   └── mi_componente.h
    └── mi_componente.c
```

El archivo ```CMakeLists.txt``` dentro del componente indica a IDF dónde están los archivos fuente y las cabeceras públicas. Por ejemplo:

```
idf_component_register(
    SRCS "mi_componente.c"
    INCLUDE_DIRS "include"
)
```

Si se desea agregar un nuevo componente, basta con colocar su carpeta dentro de components/ y escribir su CMakeLists.txt. IDF detecta automáticamente todos los componentes presentes en el directorio. De esta manera, el archivo ```main.c``` solo necesita incluir el header del componente y llamar sus funciones.

Si de pura casualidad el compilador no detecta el componente a utilizar, se puede editar el archivo ```main/CMakeLists.txt``` para agregar explicitamente la dependencia de dicho componente:

``` CMakeLists.txt
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES mi_componente   # ← Declara dependencia explícita
)
```

> [!TIP]
> Por lo general, los componentes son paquetes de trabajo ya hechos y desarrollados por otros usuarios y/u organizaciones. La idea principal de un componente o paquete, en el mundo de desarrollo de software en general, es evitar el arduo trabajo de programar algo que ya está hecho y utilizar el código que otro programador ya realizó anteriormente.
>
> Los componentes pueden ser buscados en el [Registro de Componentes Oficial de Espressif](https://components.espressif.com/)

> [!NOTE]
> Por ejemplo, un componente especial que integro comunmente es el [Componente Oficial de Microros para IDF](https://github.com/micro-ROS/micro_ros_espidf_component) para la integración del microcontrolador ESP32 en proyectos de robótica con ROS2.

## Devcontainer

Se integró un ```.devcontainer``` en el repositorio para desarrollar con IDF sin la necesidad de descargar y configurar el SDK de Espressif manualmente, solamente es necesario tener VSCode, Docker y la extensión de VSCode para devcontainers ([ms-vscode-remote.remote-containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)).