
# Introduction

OpenStreetMap  (OSM)  est  un  projet  qui  a  pour  but  de
constituer une base de données géographiques libre du monde
(permettant  par  exemple  de  créer  des  cartes  sous  licence
libre), en utilisant le système GPS et d'autres données libres.

Le but de ce projet est de réaliser en trinôme un logiciel de rendu (renderer)
de cartes OpenStreetMap en C. Il est capable de lire un fragment de carte
au format XML standard d'OpenStreetMap et de l'aficher à l'écran en utilisant des primitives
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
- indent : pour formater le code.
- doxygen : pour générer la documentation.

## 2. Makefile

Pour compiler le projet :
~~~~~~~~~~~~~~~{shell}
make
~~~~~~~~~~~~~~~
Pour générer la documentation :
~~~~~~~~~~~~~~~{shell}
doxygen doc/doxygen.cfg
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
