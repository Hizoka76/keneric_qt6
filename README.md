# keneric

**Documentation en cours de création**

## Version Française :
Cette nouvelle version pour KDE6 fait suite à https://github.com/Hizoka76/keneric qui fonctionnait pour KDE5.

Il a fallu modifier le fonctionnement de keneric et de son makefile pour le rendre compatible avec KDE6.

De nombreuses choses ont évoluées entre KDE5 et KDE6.


### Description :
keneric est un générateur de vignettes pour plasma KDE6 qui utilise un script (bash ou python) pour créer ces vignettes.

La base du système a été créé par Rog131 <samrog131@hotmail.com> mais a complétmeent évolué.


### Installation :
#### Depuis les sources :
Pour les dérivés d'Ubuntu, la compilation necessite les paquets : **cmake build-essential kf6-kio-dev kf6-kcoreaddons-dev kf6-kcoreaddons-dev**.

Une fois dans le dossier, le plus simple est de procéder ainsi :
```
mkdir builddir
cd builddir
cmake ..
sudo make install
```
Le fichier **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator/keneric.so** est créé.

Avec le paquet **checkinstall**, il est possible de remplacer `sudo make install` par `sudo checkinstall` pour générer un fichier deb.

#### Depuis le binaire :
Extraire le binaire du fichier tar.gz : **https://github.com/Hizoka76/keneric/releases/latest**.

Le déplacer dans le dossier **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator**.


### Principe de fonctionnement :
#### Fichiers desktop (déprécié) :
Ces fichiers ne fonctionnent plus avec KDE6.
Il n'est plus aussi facile de créer des liens dans Dolphin, les mimetypes sont définis dans le fichier **kenericthumbnail.json** qui doit être recompilé après modification.

#### Fichier keneric.so :
Voir ci-dessus pour son installation.

Il appelle le script keneric et attent que celui-ci lui rende la main.
Le script reçoit une adresse de sortie de vignette dna sle dossier /tmp/keneric.
keneric.so récupère ce fichier et si la vignette est valide, elle sera chargée et fournie au navigateur de fichiers qui l'affichera.

#### Script keneric :
Ce script est appelé par keneric.so qui lui fourni les arguments suivants :
 - Le fichier en attente de vignette.
 - Le mimetype du fichier en attente de vignette.
 - L'emplacement et le nom de la vignette de sortie.

Le script doit être placé dans un dossier du path, pour voir ces dossiers :
```
echo "$PATH"
```

#### Scripts sourcés par keneric :
Afin de faciliter le développement de nouvelles fonctionnalités, keneric charge des sous-scripts.
Toutes les explications sur le fonctionnement des sous-scripts sont dans le [dossier script](scripts).


#### Fichier keneric.conf :
Fichier présent à l'adresse ~/.config/keneric.conf.
Il est utilisé par keneric.so et par le script keneric.

Toutes les informations sur le fichier sont dans le [dossier config](config)

### Exemples de rendus possibles :
#### Script Directory-Covert : Avec un fichier "cover" dans le dossier.
![Directory-Cover](/readme/Directory-Cover.png)


#### Script Directory-Disk : Avec un fichier "disk" dans le dossier.
![Directory-Disk](/readme/Directory-Disk.png)


#### Script Directory-Full : Avec un fichier "full" dans le dossier.
![Directory-Full](/readme/Directory-Full.png)


#### Script Video-mkv-Cover : Avec une image dans un fichier mkv.
La couleur du contour s'adapte à la résolution de la vidéo et à la 3D.
![Video-mkv-Cover](/readme/Video-mkv-Cover.png)


### Services :
Les fichiers desktop ont été modifiés pour s'adapter à KDE6.
Il est **impératif** de rendre ces fichiers exécutables.
Ces fichiers doivent maintenant être placés dans le dossier **.local/share/kio/servicemenus/** (//ou /usr/share/kio/servicemenus//).

Des services en liens sont égalements proposés :
 - Le [dossier KenericHashFile](KenericHashFile) propose de copier le hash d'un élément.
 - Le [dossier KenericRemoveThumbnails](KenericRemoveThumbnails) propose de supprimer les vignettes d'éléments.
 - Le [dossier KenericCustomIcon](KenericCustomIcon) propose de facilité l'utilisation de vignettes personnalisées.
 - Le [dossier KenericDeleteCustomIcon](KenericDeleteCustomIcon) propose de supprimer les vignettes personnalisées.
