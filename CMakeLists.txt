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

kcoreaddons_add_plugin(keneric INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

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

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
