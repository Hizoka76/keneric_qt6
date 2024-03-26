# keneric

**Documentation en cours de création**

## Version Française :
Cette nouvelle version pour KDE6 fait suite à https://github.com/Hizoka76/keneric qui fonctionnait pour KDE5.

Il a fallu modifier le fonctionnement de keneric et de son makefile pour le rendre compatible avec KDE6.

De nombreuses choses ont évoluées entre KDE5 et KDE6.


### Description :
keneric est un générateur de vignettes pour plasma KDE6 qui utilise un script (bash ou python) pour créer ces vignettes.

L'idée du de base a été créé par Rog131 <samrog131@hotmail.com> mais le fonctionnement a grandement évolué.


### Installation :
#### Depuis les sources :
Pour les dérivés d'Ubuntu, la compilation nécessite l'installation de paquets : 
```
sudo apt install cmake build-essential kf6-kio-dev kf6-kcoreaddons-dev kf6-kcoreaddons-dev
```

Télécharger le contenu du git.

Une fois dans le dossier contenant les fichiers du git, le plus simple est de procéder ainsi :
```
mkdir builddir
cd builddir
cmake ..
sudo make install
```
Les fichiers suivant sont générés :
 - **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator/keneric.so**
 - **/usr/share/metainfo/org.kde.keneric.metainfo.xml**

Avec le paquet **checkinstall**, il est possible de remplacer `sudo make install` par `sudo checkinstall` pour générer un fichier deb.

#### Depuis le binaire :
Extraire le binaire du fichier tar.gz : **https://github.com/Hizoka76/keneric_qt6/releases/latest**.

Déplacer le fichier **keneric.so** dans le dossier **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator**.


### Principe de fonctionnement :
#### Fichiers desktop (dépréciés) :
Ces fichiers qui servaient à ajouter des liens entre **keneric.so** et **Dolphin** ne fonctionnent plus avec KDE6.

Il n'est malheureusement plus aussi facile de créer des liens dans **Dolphin**.
Les mimetypes sont maintenant définis dans le fichier **kenericthumbnail.json** qui doit être recompilé après modification.

Il serait envisageable de n'utiliser que keneric en indiquant un mimetype *application/octet-stream* (qui semble remplacer *all/all-files*).
Il faudrait alors gérer les différents mimetypes dans des sous-scripts keneric.

#### Fichier keneric.so :
**Dolphin** va l'utiliser pour générer une vignette.
**keneric.so** appelle le script **keneric** en lui fournissant des arguments et attend que celui-ci lui rende la main.

Les arguments passés au script sont :
 - L'adresse du fichier attendant une vignette.
 - Le mimetype de ce fichier.
 - L'URL de la vignette temporaire (*/tmp/keneric/...*) que chargera **keneric.so**

**keneric.so** chargera cette vignette temporaire et, si est valide, la fournira à **Dolphin** qui l'affichera.

#### Script keneric :
Ce script est appelé par **keneric.so** et ne contient pas d'extension afin de pouvoir utiliser plusieurs langages comme **bash** ou **python**.

Le script **keneric** doit être placé dans un dossier du path, pour voir ces dossiers :
```
echo "$PATH"
```

#### Script bash proposé
Le git propose un script **keneric** gérant les mimetypes *mkv* et *directory*.

Afin de faciliter le développement de nouvelles fonctionnalités, ce script charge des sous-scripts.

##### Scripts sourcés par keneric :
Toutes les explications sur le fonctionnement des sous-scripts sont dans le [dossier script](scripts).

#### Fichier keneric.conf :
Fichier présent à l'adresse **~/.config/keneric.conf**.
Il est utilisé par **keneric.so** et par le script **keneric** proposé.

Toutes les informations sur le fichier sont dans le [dossier config](config)

### Exemples de rendus par le script proposé :
#### Script Directory-Covert : Il suffit de déposer un fichier "cover" dans le dossier.
![Directory-Cover](/readme/Directory-Cover.png)


#### Script Directory-Disk : Il suffit de déposer un fichier "disk" dans le dossier.
![Directory-Disk](/readme/Directory-Disk.png)


#### Script Directory-Full : Il suffit de déposer un fichier "full" dans le dossier.
![Directory-Full](/readme/Directory-Full.png)


#### Script Video-mkv-Cover : Il suffit que le fichier mkv contienne une image.
La couleur du contour s'adapte à la résolution de la vidéo et à la 3D.
![Video-mkv-Cover](/readme/Video-mkv-Cover.png)


### Services :
Les fichiers desktop ont été modifiés pour s'adapter à KDE6.
Il est **impératif** de rendre ces fichiers exécutables.
Ces fichiers doivent maintenant être placés dans le dossier **.local/share/kio/servicemenus/** (//ou /usr/share/kio/servicemenus//).
__SEPARATOR__ ne fonctionne plus en KDE6.

Des services en liens sont également proposés :
 - Le [dossier KenericHashFile](KenericHashFile) propose de copier le hash d'un élément.
 - Le [dossier KenericRemoveThumbnails](KenericRemoveThumbnails) propose de supprimer les vignettes d'éléments.
 - Le [dossier KenericCustomIcon](KenericCustomIcon) propose de facilité l'utilisation de vignettes personnalisées.
 - Le [dossier KenericDeleteCustomIcon](KenericDeleteCustomIcon) propose de supprimer les vignettes personnalisées.
