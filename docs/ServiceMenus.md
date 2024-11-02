# Service-Menus

## Version Française :
### Présentation :
Les service-menus permettent d'ajouter des actions via le clic droit lorsque l'on est dans **Dolphin**.

Ce sont des fichiers **.desktop** à installer dans un dossier de KDE6 :
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

Il est **impératif** de rendre ces fichiers exécutables via un clic droit ou via `chmod +x *.desktop`.

Ces fichiers **.desktop** peuvent exécuter des commandes directes ou exécuter des commandes externes.
Ces commandes doivent être accessible dans un dossier du path : `echo "$PATH"`

**SEPARATOR** ne fonctionne plus en KDE6.

Plus d'informations dans les services fournis et sur https://develop.kde.org/docs/apps/dolphin/service-menus/.


## English version:
### Presentation:
Service menus allow you to add actions via right-click while in **Dolphin**.

These are **.desktop** files to be installed in a KDE6 folder:
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

It is **imperative** to make these files executable via right-click or `chmod +x *.desktop`.

These **.desktop** files can execute direct commands or external commands.
These commands must be accessible in a path folder: `echo "$PATH"`

**SEPARATOR** no longer works in KDE6.

For more information, see the services provided and https://develop.kde.org/docs/apps/dolphin/service-menus/.
