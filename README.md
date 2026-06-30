# MusicaPASO — Streaming de Música

**Integrantes del equipo:**

- Paulo Araya - ICCI -21.918.080-2
- Diego Malebran - ICCI - 21.661.740-1
- Benjamín Sierra - ICCI - 22.105.031-2

---

## Descripción

StreamList es una aplicación de consola escrita en C++ que simula un reproductor de música estilo streaming. Permite cargar un catálogo de canciones desde un archivo de texto y gestionar una lista de reproducción mediante la clase `ListaReproduccion` que implementa una lista doblemente enlazada. El usuario puede pausar, avanzar, retroceder, activar modo aleatorio y configurar repetición de canciones. El estado del reproductor se guarda automáticamente en un archivo de configuración, permitiendo retomar la sesión donde se dejó.

---

### Instrucciones para compilar y correr el codigo

El codigo fue trabajado utilizando Arch y Ubuntu Linux respectivamente, por lo tanto, las instrucciones serán para el compilador **gcc**.

Para compilarlo y correrlo, se utilizó el siguiente comando:

```
git clone https://github.com/MotelPaso/T1Estructuras
cd T1Estructuras/src
g++ main.cpp -o taller1
./taller1
```

Si se desea revisar utilizando otro sistema operativo, se puede utilizar el archivo `taller1` del repositorio con los siguientes comandos:

```
git clone https://github.com/MotelPaso/T1Estructuras
cd T1Estructuras/src
./taller1
```

> **Nota:** El archivo `music_source.txt` debe estar en la carpeta raíz del repositorio (`T1Estructuras/`) para que el programa cargue las canciones correctamente.

---

## Funcionamiento de la aplicación

Al iniciar, el programa carga automáticamente el catálogo de canciones desde `music_source.txt` y restaura el estado previo del reproductor desde `status.cfg` (si existe).

### Menú principal

| Tecla | Acción                                                               |
| ----- | -------------------------------------------------------------------- |
| `W`   | Reproducir / Pausar la canción actual                                |
| `Q`   | Retroceder a la pista anterior                                       |
| `E`   | Avanzar a la pista siguiente                                         |
| `S`   | Activar / Desactivar modo aleatorio                                  |
| `R`   | Ciclar modo de repetición: Desactivado → Repetir una → Repetir todas |
| `A`   | Ver y gestionar la lista de reproducción actual                      |
| `L`   | Ver el listado completo de canciones registradas                     |
| `X`   | Guardar estado y salir                                               |

### Gestión de canciones (`L`)

Desde el listado de canciones se pueden realizar las siguientes acciones:

- **`R<num>`** — Reproducir una canción específica (ej: `R3` reproduce la canción número 3, rearmando la lista desde ahí)
- **`A<num>`** — Agregar una canción al final de la lista de reproducción actual
- **`N`** — Agregar una nueva canción al registro (solicita título, autor, álbum, año, duración y ruta)
- **`D<num>`** — Eliminar una canción del registro y de la lista de reproducción
- **`V`** — Volver al menú principal

### Gestión de lista de reproducción (`A`)

- **`S<num>`** — Saltar directamente a una canción dentro de la cola (ej: `S2`)
- **`V`** — Volver al menú principal

### Persistencia del estado

Cada vez que se realiza una acción, el programa guarda automáticamente en `status.cfg`:

- Índice de la canción actual
- Estado de reproducción (reproduciendo / pausado)
- Estado del modo aleatorio
- Tipo de repetición activo (`R0`, `R1` o `RA`)
