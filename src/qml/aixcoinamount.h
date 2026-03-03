// Copyright (c) 2024-2025 The Aixcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIXCOIN_QML_AIXCOINAMOUNT_H
#define AIXCOIN_QML_AIXCOINAMOUNT_H

#include <consensus/amount.h>

#include <QObject>
#include <QString>

class AixcoinAmount : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Unit unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(QString unitLabel READ unitLabel NOTIFY unitChanged)
    Q_PROPERTY(QString display READ toDisplay WRITE fromDisplay NOTIFY displayChanged)
    Q_PROPERTY(qint64 satoshi READ satoshi WRITE setSatoshi NOTIFY amountChanged)

public:
    enum class Unit {
        AIX,
        SAT
    };
    Q_ENUM(Unit)

    explicit AixcoinAmount(QObject *parent = nullptr);

    Unit unit() const;
    void setUnit(Unit unit);
    QString unitLabel() const;

    QString toDisplay() const;
    void fromDisplay(const QString& new_amount);
    qint64 satoshi() const;
    void setSatoshi(qint64 new_amount);

    bool isSet() const { return m_isSet; }

    Q_INVOKABLE void format();

    static QString satsToAixString(qint64 sat);

public Q_SLOTS:
    void flipUnit();
    void clear();

Q_SIGNALS:
    void unitChanged();
    void amountChanged();
    void displayChanged();

private:
    QString sanitize(const QString& text);
    static qint64 aixToSats(const QString& aix);

    qint64 m_satoshi{0};
    bool m_isSet{false};
    Unit m_unit{Unit::AIX};
};

#endif // AIXCOIN_QML_AIXCOINAMOUNT_H
