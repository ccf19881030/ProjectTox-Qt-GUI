/*
    Copyright (C) 2013 by Martin Kröll <technikschlumpf@web.de>

    This file is part of Tox Qt GUI.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the COPYING file for more details.
*/

#ifndef SMILEYPACK_HPP
#define SMILEYPACK_HPP

#include <QObject>
#include <QPair>
#include <QStringList>
#include "messages/smiley.hpp"


class Smileypack : public QObject
{
    Q_OBJECT
public:
    typedef QList<QPair<QString, QStringList>> SmileypackList;

    explicit Smileypack(QObject *parent = 0);
    explicit Smileypack(const QByteArray &savedData, QObject *parent = 0);
    void operator=(const Smileypack &other);

    bool parseFile(const QString &filePath);

    const QByteArray save();
    void restore(const QByteArray &array);

    const QString &getThemeFile() const             { return themeFile;   }
    void           setThemeFile(const QString &x)   { themeFile = x;      }
    const QString &getName() const                  { return name;        }
    void           setName(const QString &x)        { name = x;           }
    const QString &getAuthor() const                { return author;      }
    void           setAuthor(const QString &x)      { author = x;         }
    const QString &getDescription() const           { return description; }
    void           setDescription(const QString &x) { description = x;    }
    const QString &getVersion() const               { return version;     }
    void           setVersion(const QString &x)     { version = x;        }
    const QString &getWebsite() const               { return website;     }
    void           setWebsite(const QString &x)     { website = x;        }
    const QString &getIcon() const                  { return icon;        }
    void           setIcon(const QString &x)        { icon = x;           }
    const SmileypackList &getList() const               { return list;        }
    void              setList(const SmileypackList &x)  { list = x;           }
    bool  isEmoji() const                           { return emoji;       }
    void setEmoji(bool x)                           { emoji = x;          }

    static const QString& packDir();
    static QString desmilify(QString htmlText);
    static QString deemojify(QString text);
    static QString resizeEmoji(QString text);
    static const SmileypackList emojiList();
    static const SmileypackList defaultList();

private:
    QString themeFile;
    QString name;
    QString author;
    QString description;
    QString version;
    QString website;
    QString icon;
    SmileypackList list;
    bool emoji;

    // Parser functions
    enum ParserStates{
        StateHead,
        StateSmileys
    };
    void processLine(const QString &xLine, const QString &xPath, ParserStates &xState);
};

QDataStream &operator<<(QDataStream &out, const Smileypack &pack);
QDataStream &operator>>(QDataStream &in, Smileypack &pack);

#endif // SMILEYPACK_HPP
