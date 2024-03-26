# KenericHashFile

## Version Française :
### Présentation :
Ce service menu permet de copier dans le presse papier le hash md5 de l'élément sélectionné.

Ainsi, il est facile de retrouver la vignette dans le dossier **~/.cache/thumbnails** ou encore de personnaliser l'icône de l'item dans le fichier de config **~/.config/keneric.conf**.

### Installation :
Le fichier **keneric-hash-file.desktop** doit être mis dans un dossier du path de KDE6 :
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

Ce fichier doit être rendu exécutable (via un clic droit par exemple) ou via :
```
chmod +x keneric-hash-file.desktop
```

Le fichier **keneric-hash-file** doit être mis dans le path :
```
echo "$PATH"
```

### Utilisation :
Il suffit de faire un clic droit sur l'élément (fichier ou dossier) puis de choisir **Keneric Actions** et enfin **Copier le hash md5 du fichier**.


## English version:
### Presentation:
This menu service allows to copy in the clipboard the md5 hash of the selected item.

Thus, it is easy to find the thumbnail in the **~/.cache/thumbnails** folder or to customize the icon of the item in the Keneric config file **~/.config/keneric.conf**.

### Installation:
The **keneric-hash-file.desktop** file should be put in a folder in the KDE6 path:
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

This file must be made executable (by right-clicking, for example) or via :
```
chmod +x keneric-hash-file.desktop
```

The **keneric-hash-file** must be put in the path :
```
echo "$PATH"
```

### Usage:
Just right click on the item (file or folder) then choose **Keneric Actions** and finally **Copy the md5 hash of the file**.
