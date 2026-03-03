// Copyright (c) 2024-2025 The Aixcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qml/aixcoinamount.h>

#include <QRegExp>
#include <QStringList>

AixcoinAmount::AixcoinAmount(QObject* parent)
    : QObject(parent)
{
}

QString AixcoinAmount::sanitize(const QString &text)
{
    QString result = text;

    // Remove any invalid characters
    result.remove(QRegExp("[^0-9.]"));

    // Ensure only one decimal point
    QStringList parts = result.split('.');
    if (parts.size() > 2) {
        result = parts[0] + "." + parts[1];
    }

    // Limit decimal places to 8
    if (parts.size() == 2 && parts[1].length() > 8) {
        result = parts[0] + "." + parts[1].left(8);
    }

    return result;
}

qint64 AixcoinAmount::satoshi() const
{
    return m_satoshi;
}

void AixcoinAmount::setSatoshi(qint64 new_amount)
{
    m_isSet = true;
    if (m_satoshi != new_amount) {
        m_satoshi = new_amount;
        Q_EMIT amountChanged();
    }
}

void AixcoinAmount::clear()
{
    if (!m_isSet && m_satoshi == 0) {
        return;
    }
    m_satoshi = 0;
    m_isSet = false;
    Q_EMIT amountChanged();
}

AixcoinAmount::Unit AixcoinAmount::unit() const
{
    return m_unit;
}

void AixcoinAmount::setUnit(const Unit unit)
{
    m_unit = unit;
    Q_EMIT unitChanged();
    Q_EMIT displayChanged();
}

QString AixcoinAmount::unitLabel() const
{
    switch (m_unit) {
    case Unit::BTC: return "₿";
    case Unit::SAT: return "sat";
    }
    assert(false);
}

void AixcoinAmount::flipUnit()
{
    if (m_unit == Unit::BTC) {
        m_unit = Unit::SAT;
    } else {
        m_unit = Unit::BTC;
    }
    Q_EMIT unitChanged();
    Q_EMIT displayChanged();
}

QString AixcoinAmount::satsToBtcString(qint64 sat)
{
    const bool negative = sat < 0;
    qint64 absSat = negative ? -sat : sat;

    const qint64 wholePart = absSat / COIN;
    const qint64 fracInt = absSat % COIN;
    QString fracPart = QString("%1").arg(fracInt, 8, 10, QLatin1Char('0'));

    QString result = QString::number(wholePart) + '.' + fracPart;
    if (negative) {
        result.prepend('-');
    }
    return result;
}

QString AixcoinAmount::toDisplay() const
{
    if (!m_isSet) {
        return "";
    }
    if (m_unit == Unit::SAT) {
        return QString::number(m_satoshi);
    } else {
        return satsToBtcString(m_satoshi);
    }
}

qint64 AixcoinAmount::btcToSats(const QString& btcSanitized)
{
    if (btcSanitized.isEmpty() || btcSanitized == ".") return 0;

    QString cleaned = btcSanitized;
    if (cleaned.startsWith('.')) cleaned.prepend('0');

    QStringList parts = cleaned.split('.');
    const qint64 whole = parts[0].isEmpty() ? 0 : parts[0].toLongLong();
    qint64 frac = 0;
    if (parts.size() == 2) {
        frac = parts[1].leftJustified(8, '0').toLongLong();
    }

    return whole * COIN + frac;
}

void AixcoinAmount::fromDisplay(const QString& text)
{
    if (text.trimmed().isEmpty()) {
        clear();
        return;
    }

    qint64 newSat = 0;
    if (m_unit == Unit::BTC) {
        QString sanitized = sanitize(text);
        newSat = btcToSats(sanitized);
    } else {
        QString digitsOnly = text;
        digitsOnly.remove(QRegExp("[^0-9]"));
        newSat = digitsOnly.trimmed().isEmpty() ? 0 : digitsOnly.toLongLong();
    }
    setSatoshi(newSat);
}

void AixcoinAmount::format()
{
    Q_EMIT displayChanged();
}
