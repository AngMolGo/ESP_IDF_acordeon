# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Archivos_de_programa/Espressif_ToolChain/v5.2/esp-idf/components/bootloader/subproject"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/tmp"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/src/bootloader-stamp"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/src"
  "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/mis_proyectos/ESP32Dev/plantillaProyecto_ESP32_IDF/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
