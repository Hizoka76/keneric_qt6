# KenericCustomIcon

## Version Française :
### Présentation :
Ce service menu permet de seléctionner une image à utiliser comme vignette personnalisée pour des fichiers spécifiques.

Il modifie le fichier **~/.config/keneric.conf**

### Installation :
Le fichier **keneric-custom-icon.desktop** doit être mis dans un dossier du path de KDE6 :
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

Ce fichier doit être rendu exécutable (via un clic droit par exemple) ou via :
```
chmod +x keneric-custom-icon.desktop
```

Le fichier **keneric-custom-icon** doit être mis dans le path :
```
echo "$PATH"
```

### Utilisation :
Faire un clic droit sur les éléments (fichiers ou dossiers) puis de choisir **Keneric Actions** et enfin **Choisir une vignette personnalisée**.

Chercher l'image à utiliser comme vignette dans le selécteur de fichier.

Si **KenericRemoveThumbnails** est installé il sera exécuté afin de supprimer l'ancienne vignette du fichier, dans le cas contraire, c'est à vous de la supprimer.


## English version:
### Presentation:
This menu service lets you select an image to be used as a custom thumbnail for specific files.

It modifies the **~/.config/keneric.conf** file.

### Installation:
The **keneric-custom-icon.desktop** file should be put in a folder in the KDE6 path:
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

This file must be made executable (by right-clicking, for example) or via :
```
chmod +x keneric-custom-icon.desktop
```

The **keneric-custom-icon** must be put in the path :
```
echo "$PATH"
```

### Usage:
Right-click on items (files or folders) then choose **Keneric Actions** and finally **Choose a custom thumbnail**.

Search for the image you wish to use as a thumbnail in the file browser.

If **KenericRemoveThumbnails** is installed, it will be run to remove the old thumbnail from the file; otherwise, it's up to you to remove it.
