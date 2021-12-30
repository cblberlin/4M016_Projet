# 4M016_Projet
Le projet pour implémenter l'algorithme Dijkstra en c

## Installation
sous Linux: 
```bash
sudo apt-get install git
sudo apt-get install libxml2-dev
```

Et pour le programme se compiler sans erreurs
sous Linux: 
```bash
cp - R ~/include/libxml2/libxml ~/include
```
sous Windows:

Pas encore tester parce que je ne travaille pas sous windows

sous Mac le programme se compile normalement.

## Usage
```bash
## compiler le programme
make 

## Mode pour tester les algorithmes et pour avoir le temps d'execution
./bin/main

## Mode pour le lecture du ficheir osm, fait attention a la taille du fichier, si c'est trop grand, votre ordinateur peut etre crashe

## il y a encore des bugs sur tester le Dijkstra pour le graphe genere par le fichier osm, c'est peut-etre qu'il y a trop de points isole dans le graphe

./bin/main test/nom_du_fichier.osm

```
