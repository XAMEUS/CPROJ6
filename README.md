
# Introduction

OpenStreetMap  (OSM)  est  un  projet  qui  a  pour  but  de
constituer une base de donnees geographiques libre du monde
(permettant  par  exemple  de  creer  des  cartes  sous  licence
libre), en utilisant le systeme GPS et d'autres donnees libres.

Le but de ce projet est de realiser en trinôme un logiciel de rendu (renderer)
de cartes OpenStreetMap en C. Il est capable de lire un fragment de carte
au format XML standard d'OpenStreetMap et de l'acher a l'ecran en utilisant des primitives
portables de dessin.

# Compilation

## 1. Les dépendances

Pour la compilation du code source :
- SDL :
  + SDL.h
  + SDL_opengl.h
- OpenGL :
  + GL/glu.h
- Libxml :
  + libxml/parser.h
  + libxml/tree.h
- Glib

Autres :
- indent : pour formater le code (make indent).
- doxygen : pour générer la documentation (make doc).

## 2. Makefile

Pour compiler le projet :
~~~~~~~~~~~~~~~{shell}
make
~~~~~~~~~~~~~~~
Pour générer la documentation :
~~~~~~~~~~~~~~~{shell}
make doc
~~~~~~~~~~~~~~~

Pour formater le code source :
~~~~~~~~~~~~~~~{shell}
make indent
~~~~~~~~~~~~~~~

# Exemples :

<img src="https://dl.dropboxusercontent.com/u/53110380/CPROJ6/Screenshot%20-%2002042016%20-%2017%3A54%3A10.png" width="1024">
<img src="https://dl.dropboxusercontent.com/u/53110380/CPROJ6/Screenshot%20-%2002042016%20-%2017%3A52%3A21.png" width="1024">
<img src="https://dl.dropboxusercontent.com/u/53110380/CPROJ6/Screenshot%20-%2002042016%20-%2017%3A55%3A02.png" width="1024">
<img src="https://dl.dropboxusercontent.com/u/53110380/CPROJ6/Screenshot%20-%2002042016%20-%2017%3A56%3A04.png" width="1024">
