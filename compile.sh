#!/bin/bash

function Packages()
{
# Liste des paquets
DpkgList=$(dpkg -l)

# Installation des paquets
for Paquet in "${@}"
do
    # S'il y a un paquet ou un autre
    if [[ "${Paquet}" == *"|"* ]]
    then
        # Teste chaque paquet
        for SubPaquet in ${Paquet//|/ }
        do
            # Si un paquet est installé, on s'arrête là
            grep -qE "^ii  ${SubPaquet}[[:space:]]" <<< "${DpkgList}" && return 0
        done
    fi

    # Installation du 1er paquet
    if ! grep -qE "^ii  ${Paquet%%|*}[[:space:]]" <<< "${DpkgList}"
    then
        echo -e "${BLEUFONCE}Installation de ${Paquet%%|*}\n${RAZ}"
        sudo apt-get -qy install ${Paquet%%|*}
    fi
done

# Liste des paquets
DpkgList=$(dpkg -l)

# Vérification de l'installation des paquets
for Paquet in "${@}"
do
    if ! grep -qE "^ii  ${Paquet%%|*}[[:space:]]" <<< "${DpkgList}"
    then
        echo -e "${ROUGE}${Paquet%%|*} non installé !${RAZ}"
        return 1
    fi
done

# Si tout est OK
return 0
}


# Vérification des dépendnaces et installation des paquets si besoin
echo -e "\nChecking and installation of the packages..."
Packages build-essential kf6-kio-dev kf6-kcoreaddons-dev kf6-kcoreaddons-dev cmake extra-cmake-modules

# Création du dossier de build
echo -e "\n(Remove and) Création of the build folder..."
rm -rf build &>/dev/null
mkdir build

# Préparation du build
echo -e "\nPreparation of the build..."
cmake -B build/

echo -e "\nWhat do you want?"
select Action in "Just compile" "Make install" "Create an debian package"
do
    case "${Action}" in
        "Just compile")
            # Lancement du build
            cmake --build build/

            break ;;

        "Make install")
            # Lancement du build
            cmake --build build/

            # installation des fichiers
            sudo cmake --install build/

            break ;;

        "Create an debian package")
            # Lancement du build
            cmake --build build/

            # Création du fichier de description :
            echo -e "keneric, a thumbnail generator for KDE6 plasma\n\nkeneric is a thumbnail generator for KDE6 plasma that uses a script (bash or python) to create these thumbnails." > build/description-pak

            # Création du fichier postinstall
            cat << 'EOF' > build/postinstall-pak
#!/bin/sh

set -e

for user in /home/*
do
    if [ ! -e "${user}/.config/keneric.conf" ]
    then
        cp "/etc/keneric.conf" "${user}/.config/keneric.conf"
    fi
done
EOF

            # Création du fichier postrm
            cat << 'EOF' > build/postrm-pak
#!/bin/sh

set -e

if [ "${1}" = "purge" ]
then
    for user in /home/*
    do
        rm -fv "${user}/.config/keneric.conf"
    done
fi
EOF

            # Vérification de la présence du paquet checkinstall
            Packages checkinstall

            # Création et installation du paquet debian
            cd build && sudo checkinstall --fstrans=no --pkgname "keneric" --maintainer "hizo@free.fr" --pkggroup "libs" --exclude "/home" --recommends "imagemagick,mkvtoolnix,ffmpegthumbnailer,xclip,kdialog"

            break ;;
    esac
done

