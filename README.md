# CarlosBadillaArias — Proyecto 2

## Descripcion general

El jugador crea un heroe eligiendo nombre, raza y el nombre del
jefe final. Luego explora El Reino de Disandria, un mundo de 13 espacios
conectados repartidos en 3 zonas, recoge objetos, combate enemigos
por turnos y busca derrotar al jefe final para salvar el reino.

---

## Estructura del proyecto

```
CarlosBadillaArias_Proyecto2/
├── main.cpp                  # Punto de entrada
├── CMakeLists.txt            # Configuracion de compilacion
├── data/                     # Archivos JSON de configuracion del mundo
│   ├── world.json
│   ├── spaces.json
│   ├── connections.json
│   ├── items.json
│   ├── enemies.json
│   └── objectives.json
├── output/                   # Generado al terminar la partida
│   ├── adventure_log.txt
│   └── adventure_report.txt
├── include/
│   └── json.hpp              # Libreria nlohmann/json (descargada por CMake)
│
│   --- Entidades ---
├── Entity.h / .cpp           # Clase base de personajes y enemigos
├── Character.h / .cpp        # Jugador principal
├── Enemy.h / .cpp            # Enemigo base
│
│   --- Items ---
├── Item.h / .cpp             # Clase base de objetos
├── Weapon.h / .cpp           # Arma
├── Consumable.h / .cpp       # Pocion / consumible
├── KeyItem.h / .cpp          # Llave / objeto de mision
├── ItemDecorator.h / .cpp    # Decorators de items (envenenado)
├── Inventory.h               # Contenedor de items del jugador
│
│   --- Enemigos ---
├── EnemyDecorator.h / .cpp   # Decorators de enemigos (acorazado, enfurecido)
├── CombatStrategy.h / .cpp   # Estrategias de combate
├── ICombatStrategy.h         # Interfaz de estrategia
│
│   --- Mundo ---
├── Space.h / .cpp            # Space, Zone e ISpaceComponent (Composite)
├── World.h / .cpp            # Contenedor del mundo y estado global
│
│   --- Eventos ---
├── GameEvent.h / .cpp        # Clase base de eventos
├── CombatEvent.h / .cpp      # Evento de combate por turnos
├── NarrativeEvent.h / .cpp   # Evento narrativo
│
│   --- Sistema ---
├── SimulationEngine.h / .cpp # Motor principal del juego
├── FileLoader.h / .cpp       # Carga y genera archivos JSON
├── GameFactories.h / .cpp    # Fabricas de items y enemigos
├── Logger.h                  # Singleton de bitacora
├── ReportGenerator.h / .cpp  # Generador del reporte final
├── Objective.h / .cpp        # Objetivos y quest principal
│
│   --- Interfaces ---
├── IObserver.h
├── ISerializable.h
├── IUpdatable.h
└── IInteractable.h
```

---

## Controles durante el juego

| Accion                  | Entrada                            |
|-------------------------|------------------------------------|
| Moverse                 | Numero de la direccion `[1]`, `[2]`... |
| Ver inventario          | `i`                                |
| Ver estado del personaje| `s`                                |
| Equipar arma            | `e`                                |
| Recoger objeto          | Escribir el nombre exacto del objeto |
| Omitir recogida         | ENTER                              |
| Combate — Atacar        | `1`                                |
| Combate — Usar objeto   | `2`                                |
| Combate — Huir          | `3`                                |

---

## Razas disponibles

| Raza   | Ventaja                                  |
|--------|------------------------------------------|
| Humano | Stats balanceados                        |
| Elfo   | +2 ATK, alta agilidad y magia            |
| Enano  | +20 HP, +3 DEF, alta fuerza              |
| Mago   | +5 ATK, maximo poder magico              |
| Hada   | Agilidad y suerte extremas, -10 HP       |

---

## Mapa del mundo — El Reino de Disandria

El mundo tiene **13 espacios** distribuidos en 3 zonas. Dos de los
accesos estan bloqueados y requieren llaves especificas.

### Zona 1 — La Aldea (inicio)

| Espacio             | Enemigo          | Item disponible      |
|---------------------|------------------|----------------------|
| Plaza de la Aldea   | —                | Pocion de Salud      |
| Forja del Herrero   | —                | Espada Oxidada       |

### Zona 2 — Las Tierras Salvajes

| Espacio                    | Enemigo                      | Item disponible       |
|----------------------------|------------------------------|-----------------------|
| Bosque Ancestral           | Lobo del Bosque (agresivo)   | Daga Elfica           |
| Capilla en Ruinas          | La Llorona (aleatorio)       | Pocion Mayor          |
| Cruce del Rio              | Trol del Rio (acorazado)     | —                     |
| Campamento de Guerra Goblin| Jefe Guerrero Goblin         | Hacha de Guerra, Brebaje Berserker |
| Paso de Montanna           | Golem de Montanna (defensivo)| Llave de Hierro       |
| Torre del Mago             | —                            | Super Pocion          |
| Paramo *                   | —                            | Espada Vorpal         |
| La Casa de la Bruja        | —                            | Pocion de Hongos Danta (recompensa) |

> \* El Paramo se accede desde el Bosque Ancestral con el **Polvo de Hadas**
> (bloqueado, llave encontrada en las Profundidades de la Mazmorra).
> La Casa de la Bruja se accede desde el Paramo sin bloqueo.

### Zona 3 — La Mazmorra

| Espacio                       | Enemigo                              | Item disponible  |
|-------------------------------|--------------------------------------|------------------|
| Entrada de la Mazmorra        | —                                    | —                |
| Profundidades de la Mazmorra *| Caballero de las Sombras (enfurecido)| Medallon Oscuro, Polvo de Hadas |
| Trono de la Oscuridad **      | Jefe Final (enfurecido)              | —                |

> \* Requiere la **Llave de Hierro** (encontrada en el Paso de Montanna).
> \*\* Requiere el **Medallon Oscuro** (encontrado en las Profundidades).

---

## Archivos de entrada y salida

El programa carga el mundo desde archivos `.json` en la carpeta
`data/`. Si alguno no existe, lo crea automaticamente con valores
por defecto al iniciar el programa.

Al terminar la partida genera dos archivos en `output/`:

- `adventure_log.txt` — bitacora completa con todos los eventos
- `adventure_report.txt` — reporte final con resultado, personaje,
  objetivos, espacios visitados y enemigos

---

## Patrones de diseno utilizados

| Patron           | Clase(s)                                                                 |
|------------------|--------------------------------------------------------------------------|
| Singleton        | `Logger`                                                                 |
| Abstract Factory | `IItemFactory`, `IEnemyFactory`, `MedievalItemFactory`, `MedievalEnemyFactory` |
| Decorator        | `ItemDecorator`, `PoisonedItemDecorator`, `EnemyDecorator`, `ArmoredEnemyDecorator`, `EnragedEnemyDecorator` |
| Composite        | `ISpaceComponent` (interfaz), `Zone` agrupa `Space`s — `CompositeObjective` agrupa sub-objetivos |
| Strategy         | `AggressiveStrategy`, `DefensiveStrategy`, `RandomStrategy`              |
| Observer         | `IObserver` implementado por `Logger` y `CombatEvent`                    |

---

## Autor

**Carlos Badilla Arias**
Universidad Nacional de Costa Rica
Escuela de Informatica — EIF204 Programacion II
I Ciclo 2026