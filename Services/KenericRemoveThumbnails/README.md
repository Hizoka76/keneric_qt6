# KenericRemoveThumbnails

## Version Française :
### Présentation :
Ce service menu permet de supprimer les vignettes des éléments sélectionnés et de recharger l'affichage de **Dolphin**.

### Installation :
Le fichier **keneric-remove-thumbnails.desktop** doit être mis dans un dossier du path de KDE6 :
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

Ce fichier doit être rendu exécutable (via un clic droit par exemple) ou via :
```
chmod +x keneric-remove-thumbnails.desktop
```

Le fichier **keneric-remove-thumbnails** doit être mis dans le path :
```
echo "$PATH"
```

### Utilisation :
Il suffit de faire un clic droit sur l'élément (fichier ou dossier) puis de choisir **Keneric Actions** et enfin **Supprimer les vignettes des éléments** ou **Supprimer recursivement les vignettes des éléments**.


## English version:
### Presentation:
This menu service allows to delete the thumbnails's items and reload the Dolphin view.

### Installation:
The **keneric-remove-thumbnails.desktop** file should be put in a folder in the KDE6 path:
```
kf5-config --path services
```

This file must be made executable (by right-clicking, for example) or via :
```
chmod +x keneric-remove-thumbnails.desktop
```

The **keneric-remove-thumbnails** must be put in the path :
```
echo "$PATH"
```

### Usage:
Just right click on the item (file or folder) then choose **Keneric Actions* and finally **Delete thumbnails of items** ou **Recursive delete thumbnails of items**.
