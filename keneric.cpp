//    Copyright (C) 2015 Rog131 <samrog131@hotmail.com>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

// https://specifications.freedesktop.org/thumbnail-spec/thumbnail-spec-latest.html

//    keneric can use a conf file now (~/.config/keneric.conf).
//    The file can contains:
//      The folders authorized:
//          foldersAuthorized=folder1, folder2...
//
//      The folders prohibited:
//          foldersProhibited=folder1, folder2...
//
//      The icon to use for files with their md5 hash:
//          d06329310e5224bf069270f88cee59ad=IconURL_1
//          855abd06329598745624bf0699270654=IconURL_2
//          ...
//
//    If foldersAuthorized and foldersProhibited are used,
//    the file needs to be in foldersAuthorized but not in foldersProhibited.


// 2024/03/24 - v0.8 by Terence Belleguic
//  Replace ThumbCreator with ThumbnailRequest for Qt6

// 2023/12/09 - v0.7 by Terence Belleguic
//  Add path command : ~/.local/bin/

// 2023/12/09 - v0.6 by Terence Belleguic
//  log file created in tmp folder.

// 2022/01/23 - v0.5 by Terence Belleguic
//  Load of the thumbnail if exists.

// 2022/01/18 - v0.4 by Terence Belleguic
//  Added: Use of a conf file.
//  Updated: The temp thumbnail name is now the md5 hash of the final thumbnail file.
//  Updated: The executed script was renamed from stripPicture to keneric.


#include "keneric.h"

#include <QDir>
#include <QFile>
#include <QUrl>
#include <QImage>
#include <QProcess>
#include <QMimeType>
#include <QMimeDatabase>
#include <QStandardPaths>
#include <QCryptographicHash>
#include <QSettings>
#include <QTextStream>

#include <QImageReader>

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(Keneric, "kenericthumbnail.json")

Keneric::Keneric(QObject *parent, const QVariantList &args)
    : KIO::ThumbnailCreator(parent, args)
{
}

Keneric::~Keneric()
{
}



KIO::ThumbnailResult Keneric::create(const KIO::ThumbnailRequest &request)
{
    // Fichier pour lequel il faut une vignette
    QString path = request.url().toLocalFile();
    QUrl pathURL(QStringLiteral("file://"));
    pathURL.setPath(path);

    // Récupération du mime type de l'élément
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(path);

    // Encodage de l'adresse
    QByteArray pathURI = pathURL.toEncoded();

    // Hash de l'URI qui sera utilisé par le système
    QByteArray hashData = QCryptographicHash::hash(pathURI, QCryptographicHash::Md5);
    QString md5Hash = QString::fromUtf8(hashData.toHex());

    // Vignette finale
    QString pathThumb = QString(QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + QStringLiteral("/thumbnails/large/") + md5Hash + QStringLiteral(".png"));

    QImage img;

    // Si la vignette existe déjà, on la recharge directement
    // C'est le cas lorsqu'on survol un fichier pour afficher ses infos dans Dolphin
    if (QFile::exists(pathThumb))
    {
        // Chargement de la vignette existante
        QImageReader reader(pathThumb);
        QImage img = reader.read();

        // Vérifier si le chargement a réussi
        if (! img.isNull()) {
            // Le chargement a réussi, renvoyer l'image chargée
            return KIO::ThumbnailResult::pass(img);
        }
    }

    // CONFIG FILE //
    // Fichier de config
    QString settingsFile(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + QStringLiteral("/keneric.conf"));

    // Si le fichier de config existe
    if (QFile::exists(settingsFile))
    {
        // Chargement du fichier de config qui est créé si besoin
        QSettings settingsValues(settingsFile, QSettings::NativeFormat);

        // Si le md5Hash est présent dans le groupe icons du fichier de config
        if (settingsValues.contains(QStringLiteral("icons/") + md5Hash))
        {
            // Adresse de l'image
            QString imageURL = settingsValues.value(QStringLiteral("icons/") + md5Hash).toString();

            if (QFile::exists(imageURL))
            {
                // Chargement de l'image temporaire en mémoire
                QImage previewImage(imageURL);

                // Redimensionnement de l'image temporaire chargée en mémoire
                img = previewImage.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                // Ne valide que si l'image n'est pas vide
                if (!img.isNull())
                {
                    return KIO::ThumbnailResult::pass(img);
                }
            }
        }

        // Liste des groupes
        QStringList settingsGroups = settingsValues.childGroups();

        // Infos du mimetype
        QStringList mimeInfos = mime.name().split(QLatin1Char('/'));

        // Liste mimetype, grouptype, all
        QStringList groupNames;
        groupNames << mimeInfos[1] << mimeInfos[0] << QStringLiteral("all");

        // Variables testées
        QStringList variableNames;
        variableNames << QStringLiteral("itemsAuthorized") << QStringLiteral("itemsProhibited");

        QString slash = QStringLiteral("/");

        for (const QString &groupName : groupNames)
        {
            // Si le fichier de config ne contient pas le groupe
            if (! settingsGroups.contains(groupName))
            {
                continue;
            }

            // Si le groupe est présent
            for (const QString &variableName : variableNames)
            {
                // Si le fichier de config ne contient pas la clé
                if (! settingsValues.contains(groupName + slash + variableName))
                {
                    continue;
                }

                // Liste des dossiers
                QStringList folders;
                if (settingsValues.value(groupName + slash + variableName).metaType().id() == QMetaType::QStringList)
                {
                    folders = settingsValues.value(groupName + slash + variableName).toStringList();
                }
                else if (settingsValues.value(groupName + slash + variableName).metaType().id() == QMetaType::QString)
                {
                    folders << settingsValues.value(groupName + slash + variableName).toString();
                }

                // S'il y a la clé itemsAuthorized
                if (variableName == QStringLiteral("itemsAuthorized"))
                {
                    // Variable bloquante
                    bool Stop = true;

                    // Pour chaque dossier à ne pas scanner / pour chaque valeur de la clé
                    for (const QString &folder : folders)
                    {
                        // Débloque la variable si l'élément travaillé est l'enfant de l'élément ou est l'élément lui-même
                        QUrl folderURL(folder);
                        if (folderURL.isParentOf(pathURL) || folderURL == pathURL)
                        {
                            Stop = false;
                            break;
                        }
                    }

                    // Arrêt de la fonction si l'élément n'est pas autorisé
                    if (Stop)
                    {
                        return KIO::ThumbnailResult::fail();
                    }
                }

                // S'il y a la clé itemsProhibited
                else if (variableName == QStringLiteral("itemsProhibited"))
                {
                    // Pour chaque dossier à ne pas scanner / pour chaque valeur de la clé
                    for (const QString &folder : folders)
                    {
                        // Arrêt de la fonction si l'élément travaillé est l'enfant de l'élément ou l'élément lui-même
                        QUrl folderURL(folder);
                        if (folderURL.isParentOf(pathURL) || folderURL == pathURL)
                        {
                            return KIO::ThumbnailResult::fail();
                        }
                    }
                }
            }

            // Arrêt de la boucle si on avait un groupe correspondant
            break;
        }
    }
    // CONFIG FILE FIN //


    // Dossier temporaire dans lequel le script keneric devra déposer la vignette
    QString kenericDirectory(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + QStringLiteral("/keneric/"));

    // Création du dossier temporaire si besoin, doit être sur le disque que le dossier des vignettes
    QDir directory(kenericDirectory);
    if (!directory.exists())
    {
        directory.mkpath(QStringLiteral("."));
    }

    // Vignette temporaire attendue par Keneric
    QString protoThumbnail(kenericDirectory + md5Hash);

    // Nom du programme appelé qui doit créé la vignette temporaire
    QString program = QStringLiteral("keneric");

    // Arguments qui seront donnés au programme ci-dessus
    QStringList arguments;
    arguments << path << mime.name() << protoThumbnail;

    // Exécution du script avec les arguments puis attente de sa fin d'exécution avec un parent vide
    QProcess startAction;
    startAction.start(program, arguments);
    startAction.waitForFinished();



    // Récupération de l'environnement actuel
    //QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    // Ajout du PATH ~/.local/bin/
    // QString customPath = QDir::homePath() + "/.local/bin/";
    //env.insert("PATH", env.value("PATH") + ":" + customPath);

    //QObject *parent = nullptr;
    //QProcess *startAction = new QProcess(parent);
    //startAction->setProcessEnvironment(env); // Ajout du path local
    //startAction->start(program, arguments);
    //startAction->waitForFinished();


    // Si le script a bien créé l'image temporaire
    QFile thumbnailFile(protoThumbnail);
    if (thumbnailFile.exists())
    {
        // Chargement de l'image temporaire en mémoire
        QImage previewImage(protoThumbnail);

        // Redimensionnement de l'image temporaire chargée en mémoire
        img = previewImage.scaled(256, 256, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Suppression de l'image temporaire
        QFile::remove(protoThumbnail);

        return KIO::ThumbnailResult::pass(img);
    }

    return KIO::ThumbnailResult::fail();
}

#include "keneric.moc"


