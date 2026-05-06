# Réponse au TD 07

## Exercice 1

Commande utilisé pour extraire les données du fichier OpenStreetMap et les transformer en graphe :

```
./osmGraph.exe extract data/test.osm data/test_extract.graph
```

---

Commande utilisé pour simplifier le graphe :

```
.\OSM_GRAPH.exe simplify ./data/test_extract.graph
```

---

Commande utilisé pour visualiser le graphe :

```
.\OSM_GRAPH.exe visualize ./data/test_extract.graph
```

## Exercice 2

### Question 1

> La structure **_WeightedGraph_** se situe dans le fichier : **_./src/dataStructure/weightedGraph.hpp_**.

Elle sert à définir le graphe en lui-même et les fonctions qui vont avec : liste des points du graphe, ajout de points, supression de points, ajout de liens, etc.

> La structure **_PositionedGraph_** se situe dans le fichier : **_./src/osm/positionedGraph.hpp_**.

Elle sert à stocker la position des points du graphe.

=> La différence c'est que **_PositionedGraph_** stocke les positions des points alors que **_WeightedGraph_** stocke leur IDs et le poids de leur liens.

### Question 2

> Extraction OSM

Récupère les données du fichier **_OSM_** (points, chemins, limites), retire les chemins qui nous intéresses pas et créer une varible **_graph_** du type **_PositionedGraph_** avec les informations traitées.

> Simplification

Simplifie le graphe formé en enlevant les points non-connectés au graphe principale et en retirant les points inutiles.

> Visualize

Ouvre une fenêtre où le graphe mis en input est affiché.

### Question 3

Dans la simplification, il y a :

- Si l'angle entre deux point est proche d'une limite fixé, on retire un point et on reconnecte les liens à ce lui qui reste

- On groupe les points qui sont proches, on fusionne les clusters proche, on retire les cluster vide, on corrige les erreurs de superposition des points en prenant le cluster le plus proche du point, on retire les groupes de deux points et on retire les points qui sont sur les bords et qui sont trop court par rapport à une valeur.

- On garde seulement le plus gros cluster de points et on retire les autres.
