#!/bin/bash

# Obtener el directorio del script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Ejecutar el script de Python para configurar el path
python3 "$SCRIPT_DIR/Controlador/set_gazebo_path.py"

# Lanzar Gazebo con el archivo map.world.xml
gazebo "$SCRIPT_DIR/mundos/map.world.xml"

