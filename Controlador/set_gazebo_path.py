import os

def agregar_al_path():
    # Obtener la ruta absoluta del directorio del script
    repo_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Ruta del directorio de modelos
    modelos_path = os.path.join(repo_dir, "modelos")

    # Agregarlo a GAZEBO_MODEL_PATH
    os.environ["GAZEBO_MODEL_PATH"] = modelos_path + ":" + os.environ.get("GAZEBO_MODEL_PATH", "")

    print(f"Ruta añadida a GAZEBO_MODEL_PATH: {modelos_path}")
    print(f"Nuevo GAZEBO_MODEL_PATH: {os.environ['GAZEBO_MODEL_PATH']}")

    return modelos_path

if __name__ == "__main__":
    agregar_al_path()

