# KenericDeleteCustomIcon

## Version Française :
### Présentation :
Ce service menu permet de supprimer les vignettes personnalisées des éléments sélectionnés.

Il modifie le fichier **~/.config/keneric.conf**

### Installation :
Le fichier **keneric-delete-custom-icon.desktop** doit être mis dans un dossier du path de KDE6 :
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

Ce fichier doit être rendu exécutable (via un clic droit par exemple) ou via :
```
chmod +x keneric-delete-custom-icon.desktop
```

Le fichier **keneric-delete-custom-icon** doit être mis dans le path :
```
echo "$PATH"
```

### Utilisation :
Il suffit de faire un clic droit sur l'élément (fichier ou dossier) puis de choisir **Keneric Actions** et enfin **Supprimer le lien de la vignette personnalisée**.


## English version:
### Presentation:
This menu service removes custom thumbnails from selected items.

It modifies the **~/.config/keneric.conf** file.

### Installation:
The **keneric-delete-custom-icon.desktop** file should be put in a folder in the KDE6 path:
```
qtpaths --locate-dirs GenericDataLocation kio/servicemenus
```

This file must be made executable (by right-clicking, for example) or via :
```
chmod +x keneric-delete-custom-icon.desktop
```

The **keneric-delete-custom-icon** must be put in the path :
```
echo "$PATH"
```

### Usage:
Just right click on the item (file or folder) then choose **Keneric Actions** and finally **Remove the custom thumbnail link**.
