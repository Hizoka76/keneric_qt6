# keneric
## Version Française :
Cette nouvelle version pour KDE6 fait suite à https://github.com/Hizoka76/keneric qui fonctionnait pour KDE5.

Il a fallu modifier le fonctionnement de keneric et de son makefile pour le rendre compatible avec KDE6.

De nombreuses choses ont évoluées entre KDE5 et KDE6.


### Description :
keneric est un générateur de vignettes pour plasma KDE6 qui utilise un script (bash ou python) pour créer ces vignettes.

La version initiale a été créée par <a href="mailto:samrog131@hotmail.com">Rog131</a> mais le fonctionnement a grandement évolué.


### Installation :
#### Depuis les sources :
Pour les dérivés d'Ubuntu, la compilation nécessite l'installation de paquets : 
```
build-essential libkf6kio-dev libkf6coreaddons-dev cmake extra-cmake-modules
```

Télécharger le contenu du git.

Une fois dans le dossier, executer le fichier compile.sh (un script simple) qui permet :
 - D'installer automatiquement les paquets.
 - De compiler les sources.
 - De compiler les sources et d'installer les fichiers :
   - /usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator/keneric.so
   - /usr/share/metainfo/org.kde.keneric.metainfo.xml
 - De compiler les sources, de créer un paquet debian et de l'installer.
   - Necessite le paquet **checkinstall**.

#### Depuis le binaire :
Télécharger la **<a href="https://github.com/Hizoka76/keneric_qt6/releases/latest">dernière version</a>** du fichier tar.gz  et en extraire le binaire.

Déplacer le fichier **keneric.so** dans le dossier **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator**.

#### Depuis les fichier debian :
2 versions sont proposées :
 - La version simple qui n'installe que **keneric.so** et **org.kde.keneric.metainfo.xml**.
 - La version full qui installe également le script keneric proposé ainsi que les services.

### Activation :
Une fois le fichier **keneric.so** installé, cela ajoute une ligne (dont le texte est défini dans le fichier **kenericthumbnail.json**) dans **Dolphin** :

![Image de configuration de keneric dans Dolphin](/readme_img/EnableKenericInDolphinFr.png)

Attention à désactiver les potentiels autres générateurs de vignettes qui pourraient entrer en concurrence.

Dans le cas du script **keneric** proposé, il faut décocher ffmpegthumbnailers si présent et de celui des dossiers.


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

**keneric.so** chargera cette vignette temporaire et, si elle est valide, la fournira à **Dolphin** qui l'affichera.

#### Script keneric :
Ce script est appelé par **keneric.so**, il ne possède pas d'extension afin de pouvoir utiliser plusieurs langages comme **bash** ou **python**.

Le script **keneric** doit être placé dans un dossier du path, pour voir ces dossiers :
```
echo "$PATH"
```

##### Script bash proposé
Le git propose un script **keneric** gérant les mimetypes *mkv* et *directory*.

Toutes les explications sur son fonctionnement sont dans le [dossier Script](Script).

#### Fichier keneric.conf :
Fichier présent à l'adresse **~/.config/keneric.conf**.
Il est utilisé par **keneric.so** et par le script **keneric** proposé.

Toutes les informations et exemples de rendus sont dans le [dossier config](config).


### Services :
Des services menus sont proposés, ils sont en liens avec **keneric.so**.

Toutes les informations sont dans le [dossier Services](Services).


## English version:
This new version for KDE6 follows on from https://github.com/Hizoka76/keneric, which worked for KDE5.

The operation of keneric and its makefile had to be modified to make it compatible with KDE6.

Many things have evolved between KDE5 and KDE6.


### Description:
keneric is a thumbnail generator for KDE6 plasma that uses a script (bash or python) to create these thumbnails.

The basic idea was created by <a href="mailto:samrog131@hotmail.com">Rog131</a> but the operation has greatly evolved.


### Installation:
#### From source:
For Ubuntu derivatives, compilation requires the installation of : 
```
build-essential libkf6kio-dev libkf6coreaddons-dev cmake extra-cmake-modules
```

Download the git contents.

Once in the folder, run the compile.sh file (a simple script) which allows you to :
 - Automatically install packages.
 - Compile the sources.
 - Compile the sources and install the :
   - /usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator/keneric.so
   - /usr/share/metainfo/org.kde.keneric.metainfo.xml
 - Compile the sources, create a debian package and install it.
   - Requires **checkinstall** package.

#### From the binary :
Extract the binary from the tar.gz file: **https://github.com/Hizoka76/keneric_qt6/releases/latest**.

Move file **keneric.so** to folder **/usr/lib/x86_64-linux-gnu/qt6/plugins/kf6/thumbcreator**.

#### From debian files :
2 versions are available:
 - The simple version, which installs only **keneric.so** and **org.kde.keneric.metainfo.xml**.
 - The full version, which also installs the proposed keneric script and services.

### Activation:
Once the **keneric.so** file is installed, this adds a line (whose text is defined in the **kenericthumbnail.json** file) to **Dolphin**:

![keneric configuration image in Dolphin](/readme_img/EnableKenericInDolphinEn.png)

Be careful to deactivate any other thumbnail generators that may compete with you.

In the case of the **keneric** script, uncheck ffmpegthumbnailers if present, and uncheck ffmpegthumbnailers for folders.

### How it works :
#### Desktop files (deprecated):
These files, which were used to add links between **keneric.so** and **Dolphin**, no longer work with KDE6.

Unfortunately, it is no longer as easy to create links in **Dolphin**.
Mimetypes are now defined in **kenericthumbnail.json**, which must be recompiled after modification.

It would be possible to use keneric only, specifying an *application/octet-stream* mimetype (which seems to replace *all/all-files*).
The different mimetypes would then have to be managed in keneric sub-scripts.

#### keneric.so file:
**Dolphin** will use it to generate a thumbnail.
**keneric.so** calls the **keneric** script, providing it with arguments and waiting for it to hand over.

The arguments passed to the script are :
 - The address of the file waiting for a thumbnail.
 - The mimetype of this file.
 - The URL of the temporary thumbnail (*/tmp/keneric/...*) to be loaded by **keneric.so**.

**keneric.so** will load this temporary thumbnail and, if valid, provide it to **Dolphin** for display.

#### Script keneric :
This script is called by **keneric.so** and does not contain an extension so that it can be used with several languages such as **bash** or **python**.

The **keneric** script must be placed in a path folder, to view these folders :
```
echo "$PATH"
```

##### Proposed bash script
Git offers a **keneric** script that manages *mkv* and *directory* mimetypes.

Full details of how it works can be found in the [Script folder](Script).

#### keneric.conf file:
File located at **~/.config/keneric.conf**.
It is used by **keneric.so** and by the proposed **keneric** script.

All information and examples of rendering are in the [config folder](config).


### Services :
Menu services are available, linked to **keneric.so**.

All information is in the [Services folder](Services).
