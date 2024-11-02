# Scripts

## Version Française :

### Présentation :
Proposition d'un script **keneric** qui gérera les vignettes des vidéos, des mkv et des dossiers.
Ce script **keneric** source des sous-scripts pour faciliter son utilisation.

Voici ce que cela peut donner :

Pour les dossiers :

<img src="https://github.com/Hizoka76/keneric_qt6/blob/main/readme_img/ScriptKenericDirectoryEg.png" width="220" height="800">

Pour les fichiers matroska (mkv) :

![Screenshot d'exemples de vignettes pour les fichiers matroska.](/readme_img/VideoMatroskaCover.png)

### Fonctionnement :
Tous les scripts doivent être dans un dossier du path : 

```echo $PATH```

Les sous-scripts doivent être nommés en se basant sur le mimetype qu'ils traitent afin d'être correctement sourcés :

 - Avec un sous-script traitant les **video/x-matroska** : keneric-video-x-matroska-[0-9][0-9][0-9]-nom_script
 - Avec un sous-script traitant les **x-matroska** : keneric-x-matroska-[0-9][0-9][0-9]-nom_script
 - Avec un sous-script traitant les **video** : keneric-video-[0-9][0-9][0-9]-nom_script

Ils seront chargés si le mimetype complet ou partiel correspond. Si plusieurs fichiers ont le même mimtetype, alors le **[0-9][0-9][0-9]** determinera l'ordre de chargement.

#### Ordre théorique :
Donc, pour un fichier avec un mimetype **video/x-matroska** :

 - Keneric recherche des sous-scripts commençants par **keneric-video-x-matroska**.
    - S'il y en a : keneric-video-x-matroska-**001**-mkv-cover sera chargé avant keneric-video-x-matroska-**018**-mkv-other.
    - Si un sous-script crée la vignette attendue, le script s’arrêtera.
    
 - Si la vignette n'est toujours pas créée, keneric recherche des sous-scripts commençants par **keneric-x-matroska**.
    - S'il y en a : keneric-x-matroska-**001**-mkv-cover sera chargé avant keneric-x-matroska-**012**-mkv-other.
    - Si un sous-script crée la vignette attendue, le script s’arrêtera.
    
 - Si la vignette n'est toujours pas créée, keneric recherche des sous-scripts commençants par **keneric-video**.
    - S'il y en a : keneric-video-**001**-mkv-cover sera chargé avant keneric-video-**015**-mkv-other.
    - Si un sous-script crée la vignette attendue, le script s’arrêtera.

#### Ordre concret :
Dans les sous-scripts proposés pour la gestion des dossiers, l'ordre sera donc :

 - keneric-directory-**001**-nokeneric : Recherche un fichier noKeneric dans le dossier.
 - keneric-directory-**010**-disk : Recherche un fichier disk dans le dossier.
 - keneric-directory-**020**-full : Recherche un fichier full dans le dossier.
 - keneric-directory-**030**-cover : Recherche un fichier cover dans le dossier.

Dans le cas des fichiers matroska (mkv) :

 - keneric-x-matroska-010-mkv-cover : Traitement spécifique aux fichiers mkv.
 - keneric-video-999-all : Traitement pour toutes les vidéos.

### Fonctionnement des sous-scripts :
Ils peuvent utiliser les fonctions partagées suivantes :

 - **Dependencies** : À utiliser pour vérifier des dépendances avant d'utiliser les commandes correspondantes.
 - **SearchInFolder** : Utile pour la recherche d'un fichier dans un dossier
 - **LogFileMessage** : Fonction d'envoi de message au fichier log s'il est actif.
   - Ex de message : **LogFileMessage** "NoKeneric file found : ${Image}"
   - Ex de message d'erreur : convert ...  **|& LogFileMessage**

Ils peuvent utiliser les variables globales :

 - **FullName** : Adresse du fichier/dossier.
 - **MimeType** : Mimetype du fichier/dossier.
 - **ExportPicture** : Adresse de la vignette du fichier/dossier qui sera reprise par keneric.
 - **Thumb** : Nom de la vignette attendue
 - **ExecFolder** : Dossier du script keneric.
 - **LogRedirection** : Sorite des retours des messages log.

Il faut toujours déclarer les variables (avec leurs valeurs par défaut) avant de les tester afin d'éviter qu'un précédent sous-script ait créé des variables avec le même nom.

Un sous-script ne doit pas faire de return ou d'exit.
Un sous-script ayant créé la vignette doit l'avoir exportée vers **${ExportPicture}** et faire un **ThumbCreated=1** afin de terminer le script keneric.


## English version:
### Presentation:
Proposal for a **keneric** script to manage thumbnails for videos, mkv and folders.
This **keneric** script sources sub-scripts to facilitate its use.

Here's how it looks:

For folders :

<img src="https://github.com/Hizoka76/keneric_qt6/blob/main/readme_img/ScriptKenericDirectoryEg.png" width="220" height="800">

For matroska files (mkv) :

![Screenshot of sample thumbnails for matroska files](/readme_img/VideoMatroskaCover.png)

### Introducing :
All scripts must be in a path folder: 

```echo $PATH```

Sub-scripts must be named according to the mimetype they process, in order to be correctly sourced:

 - With sub-script processing **video/x-matroska**: keneric-video-x-matroska-[0-9][0-9][0-9]-script_name
 - With sub-script processing **x-matroska**: keneric-x-matroska-[0-9][0-9][0-9]-script_name
 - With sub-script processing **video**: keneric-video-[0-9][0-9][0-9]-script_name

They will be loaded in the above order, then by name, which is why [0-9][0-9][0-9] is useful for prioritizing them.

#### Theoric order :
So, for a file with mimetype video/x-matroska :

 - Keneric searches for sub-scripts starting with **keneric-video-x-matroska**.
    - If there are any: keneric-video-x-matroska-**001**-mkv-cover will be loaded before keneric-video-x-matroska-**012**-mkv-other.
    - If a sub-script creates the expected thumbnail, the script will stop.
      
 - If the thumbnail is still not created, keneric searches for sub-scripts starting with **keneric-x-matroska**.
    - If there are any, keneric-x-matroska-**001**-mkv-cover will be loaded before keneric-x-matroska-**016**-mkv-other.
    - If a sub-script creates the expected thumbnail, the script will stop.
      
 - If the thumbnail is still not created, keneric searches for sub-scripts starting with **keneric-video**.
    - If there are any, keneric-video-**001**-mkv-cover will be loaded before keneric-video-**019**-mkv-other.
    - If a sub-script creates the expected thumbnail, the script will stop.

#### Realistic order :
For example, in the sub-scripts proposed for folder management, the order will be:

 - keneric-directory-**001**-nokeneric: Searches for a noKeneric file in the folder.
 - keneric-directory-**010**-disk: Searches for a disk file in the folder.
 - keneric-directory-**020**-full: Search for a full file in the folder.
 - keneric-directory-**030**-cover: Searches for a cover file in the folder.

In the case of matroska (mkv) files:
 - keneric-x-matroska-010-mkv-cover: Processing specific to mkv files.
 - keneric-video-999-all: Processing for all videos.

### Sub-scripts explanation:
They can use shared functions:

 - **Dependencies**: Use to check dependencies before using linked commands.
 - **SearchInFolder**: Useful for searching for a file in a folder.
 - **LogFileMessage**: Sends a message to the log file if it is active.
    - Example message: **LogFileMessage** "NoKeneric file found: ${Image}".
    - Example of error message: convert ...  **|& LogFileMessage**

They can use the global variables :

 - **FullName**: File/folder address.
 - **MimeType**: Mimetype of the file/folder.
 - **ExportPicture**: Address of the file/folder thumbnail to be exported by keneric.
 - **Thumb**: Name of the expected thumbnail.
 - **ExecFolder**: Folder of the keneric script.
 - **LogRedirection**: Output of log message returns.

Always declare variables (with their default values) before testing them, to avoid a previous script having created variables with the same name.

A script must not return or exit.
A script that has created the thumbnail must have exported it to **${ExportPicture}** and done a **ThumbCreated=1** in order to terminate the keneric script.
