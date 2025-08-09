Para cargar una interface de mensaje o servicio hay que:
1. Descargar el componente de micro-ros en /components
2. Compilar el proyecto '''idf.py build'''. Esto compilará el componente de micro-ros y creará una carpeta llamada "micro_ros_src". En esta carpeta se creará un workspace donde deberemos de instalar (copy-paste) un package donde se instalarán nuestras interfaces personalizadas. Siguiendo con la convención de direcciones /srv y /msg.
3. El paquete se compilará *SOLAMENTE* con '''idf.py build''' del proyecto. *NO* se debe compilar el package con colcon.
4. La compilación creará una nuevo directorio en micro_ros_src/install/include con el nombre del package. Este directorio contendrá el package compilado listo para agregar a nuestro código.
5. Este directorio completo /<package> se debe copiar y pegar en el directorio micro-ros-component/include del componente.
6. Agregar las interfaces nuevas a tu código.
