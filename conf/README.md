# keneric.conf

## Version Française :
### Présentation :
**keneric.so** prend en compte le fichier de config **keneric.conf**.

Ce fichier doit être placé dans le dossier de config (généralement *~/.config/keneric.conf*).

Il peut contenir differents groupes (en respectant la casse) :
 - general :
```
[general]
# Active ou désactive le mode debug, attention à ne pas le laisser actif en dehors du mode debug !
debugMode=false
```

 - icons :
```
[icons]
# Le fichier au hash md5 d06329310e5224bf069270f88cee59ad doit utiliser l'image /home/hizoka/icone.png comme vignette.
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone.png
```

 - all (tous les éléments) :
```
[all]
# Éléments autorisés séparés par une virgule
itemsAuthorized=...

# Éléments interdits séparés par une virgule
itemsProhibited=...
```

 - Groupe du mimetype de l'élément :
```
[video]
# Éléments autorisés séparés par une virgule
itemsAuthorized=...

# Éléments interdits séparés par une virgule
itemsProhibited=...
```

 - Mimetype de l'élément :
```
[x-matroska]
# Éléments autorisés séparés par une virgule
itemsAuthorized=...

# Éléments interdits séparés par une virgule
itemsProhibited=...
```

**keneric.so** lira le fichier et ses groupes, il les traitera dans un ordre définit.

Ordre de priorité des groupes et des clés (pour l'exemple ci-dessus) :
1) icons
2) x-matroska itemsAuthorized
3) x-matroska itemsProhibited
4) video itemsAuthorized
5) video itemsProhibited
6) all itemsAuthorized
7) all itemsProhibited


### Exemple 1 :
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder3

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder3/fichier.mkv*.
1) icons : Le hash md5 du fichier correspond (*d06329310e5224bf069270f88cee59ad*).
=> Création de la vignette en utilisant */home/hizoka/icone_special.png* et arrêt de **keneric.so**.

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder3/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier est dans le dossier */home/hizoka/video/folder3*.
=> Pas de création de vignette et arrêt de **keneric.so**.

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder1/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier n'est pas dans le dossier */home/hizoka/video/folder3*.
3) video : Le fichier n'est pas dans le dossier */home/hizoka/video/folder2*.
4) all : Le fichier est dans le dossier */home/hizoka/video/folder1*.
=> Pas de création de vignette et arrêt de **keneric.so**.

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder5/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier n'est pas dans le dossier */home/hizoka/video/folder3*.
3) video : Le fichier n'est pas dans le dossier */home/hizoka/video/folder2*.
4) all : Le fichier n'est pas dans le dossier */home/hizoka/video/folder1*.
=> Création de la vignette et arrêt de **keneric.so**.


### Exemple 2 :
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder3
itemsAuthorized=/home/hizoka/video/folder1

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder1/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier est autorisé car il est dans le dossier */home/hizoka/video/folder1*.
=> Création de la vignette et arrêt de **keneric.so**.


### Exemple 3 :
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder4
itemsAuthorized=/home/hizoka/video/folder4

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder4/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier est autorisé car il est dans le dossier */home/hizoka/video/folder4*.
=> Création de la vignette et arrêt de **keneric.so**.


### Exemple 4 :
```
[all]
itemsProhibited=/home/hizoka/video/folder1
itemsAuthorized=/home/hizoka/video/folder4

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder4

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution de **keneric.so** pour le fichier */home/hizoka/video/folder4/fichier.mkv*.
1) icons : Le hash md5 ne correspond à aucune icône spécifique.
2) x-matroska : Le fichier est interdit car il est dans le dossier */home/hizoka/video/folder4*.
=> Pas de création de la vignette et arrêt de **keneric.so**.



## English version:
### Introduction:
**keneric.so** takes into account the **keneric.conf** config file.

This file must be placed in the config folder (usually *~/.config/keneric.conf*).

It can contain different groups (case-sensitive):
 - general :
```
[general]
# Enables or disables debug mode. Be careful not to leave it active when not in debug mode!
debugMode=false
```

 - icons :
```
[icons]
# File with hash md5 d06329310e5224bf069270f88cee59ad must use image /home/hizoka/icone.png as thumbnail.
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone.png
```

 - all :
```
[all]
# Allowed items separated by a comma
itemsAuthorized=...

# Prohibited items separated by a comma
itemsProhibited=...
```

 - Item mimetype group:
```
[video]
# Allowed items separated by a comma
itemsAuthorized=...

# Prohibited items separated by a comma
itemsProhibited=...
```

 - Element mimetype:
```
[x-matroska]
# Allowed items separated by a comma
itemsAuthorized=...

# Prohibited items separated by a comma
itemsProhibited=...
```

**keneric.so** will read the file and its groups, processing them in a defined order.

Priority order of groups and keys (for the above example) :
1) icons
2) x-matroska itemsAuthorized
3) x-matroska itemsProhibited
4) video itemsAuthorized
5) video itemsProhibited
6) all itemsAuthorized
7) all itemsProhibited


### Example 1:
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder3

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution of **keneric.so** for the */home/hizoka/video/folder3/file.mkv* file.
1) icons : The file's md5 hash matches (*d06329310e5224bf069270f88cee59ad*).
=> Create thumbnail using */home/hizoka/icone_special.png* and stop **keneric.so**.

Execution of **keneric.so** for the */home/hizoka/video/folder3/file.mkv* file.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is in the */home/hizoka/video/folder3* folder.
=> No thumbnail creation and **keneric.so** stopped.

Execution of **keneric.so** for */home/hizoka/video/folder1/file.mkv*.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is not in the */home/hizoka/video/folder3* folder.
3) video : The file is not in the */home/hizoka/video/folder2* folder.
4) all : The file is in the */home/hizoka/video/folder1* folder.
=> No thumbnail creation and **keneric.so** is stopped.

Execution of **keneric.so** for file */home/hizoka/video/folder5/file.mkv*.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is not in the */home/hizoka/video/folder3* folder.
3) video : The file is not in the */home/hizoka/video/folder2* folder.
4) all : The file is not in the */home/hizoka/video/folder1* folder.
=> Create thumbnail and stop **keneric.so**.


### Example 2:
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder3
itemsAuthorized=/home/hizoka/video/folder1

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution of **keneric.so** for the */home/hizoka/video/folder1/file.mkv* file.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is authorized because it is in the */home/hizoka/video/folder1* folder.
=> Create thumbnail and stop **keneric.so**.


### Example 3:
```
[all]
itemsProhibited=/home/hizoka/video/folder1

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder4
itemsAuthorized=/home/hizoka/video/folder4

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution of **keneric.so** for the */home/hizoka/video/folder4/file.mkv* file.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is authorized because it is in the */home/hizoka/video/folder4* folder.
=> Create thumbnail and stop **keneric.so**.


### Example 4:
```
[all]
itemsProhibited=/home/hizoka/video/folder1
itemsAuthorized=/home/hizoka/video/folder4

[video]
itemsProhibited=/home/hizoka/video/folder2

[x-matroska]
itemsProhibited=/home/hizoka/video/folder4

[icons]
d06329310e5224bf069270f88cee59ad=/home/hizoka/icone_special.png
```

Execution of **keneric.so** for the */home/hizoka/video/folder4/file.mkv* file.
1) icons : The md5 hash does not correspond to any specific icon.
2) x-matroska: The file is forbidden because it is in the */home/hizoka/video/folder4* folder.
=> No thumbnail creation and **keneric.so** stopped.
