// Copyright (c) 2024 The Aixcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIXCOIN_QML_CLIPBOARD_H
#define AIXCOIN_QML_CLIPBOARD_H

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>

class Clipboard : public QObject
{
    Q_OBJECT
public:
    explicit Clipboard(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void setText(const QString &text) {
        QGuiApplication::clipboard()->setText(text);
    }

    Q_INVOKABLE QString text() const {
        return QGuiApplication::clipboard()->text();
    }
};

#endif // AIXCOIN_QML_CLIPBOARD_H
