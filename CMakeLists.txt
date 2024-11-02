cmake_minimum_required(VERSION 3.16)
project(keneric)

#set(QT_MIN_VERSION "5.15.2")
set(QT_MIN_VERSION "6.0.0")

#set(KF_MIN_VERSION "5.92.0")
set(KF_MIN_VERSION "6.0.0")

#set(KDE_COMPILERSETTINGS_LEVEL "5.82")
set(KDE_COMPILERSETTINGS_LEVEL "6")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(ECMDeprecationSettings)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF${QT_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS KIO)

#kcoreaddons_add_plugin(keneric INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

kcoreaddons_add_plugin(keneric
    INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator"
    SOURCES keneric.cpp
)

target_sources(keneric PRIVATE
    keneric.cpp
)

target_link_libraries(keneric
    KF${QT_MAJOR_VERSION}::KIOGui
    KF${QT_MAJOR_VERSION}::KIOWidgets
    Qt::Gui
)



install(FILES org.kde.keneric.metainfo.xml
        DESTINATION ${KDE_INSTALL_METAINFODIR})

# Installation de l'icone
install(FILES keneric.png
        DESTINATION /usr/share/icons/hicolor/256x256/apps/)

# Installation de keneric et ses scripts
install(DIRECTORY Script/
        DESTINATION /usr/share/keneric
        FILES_MATCHING PATTERN "*")

# Installation des scripts des services
install(DIRECTORY Services/Scripts/
        DESTINATION /usr/local/bin
        FILES_MATCHING PATTERN "*")

# Installation des menu services
install(DIRECTORY Services/Desktop/
        DESTINATION /usr/share/kio/servicemenus
        FILES_MATCHING PATTERN "*")

# Installation du fichier de config
install(FILES conf/keneric.conf
        DESTINATION /etc/)

# Installation de la documentation
install(DIRECTORY docs/
        DESTINATION /usr/share/doc/keneric
        FILES_MATCHING PATTERN "*.pdf")

# Création du lien keneric dans /usr/local/bin
install(CODE "execute_process(COMMAND ln -sf /usr/share/keneric/keneric /usr/local/bin/keneric)")

# Mode execution des fichiers
install(CODE "execute_process(COMMAND chmod +x /usr/share/keneric/keneric)")
install(CODE "execute_process(COMMAND chmod +x /usr/local/bin/keneric-custom-icon)")
install(CODE "execute_process(COMMAND chmod +x /usr/local/bin/keneric-delete-custom-icon)")
install(CODE "execute_process(COMMAND chmod +x /usr/local/bin/keneric-hash-file)")
install(CODE "execute_process(COMMAND chmod +x /usr/local/bin/keneric-recursive-remove-thumbnails)")
install(CODE "execute_process(COMMAND chmod +x /usr/local/bin/keneric-remove-thumbnails)")

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
