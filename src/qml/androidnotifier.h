#ifndef AIXCOIN_QML_ANDROIDNOTIFIER_H
#define AIXCOIN_QML_ANDROIDNOTIFIER_H

#include <qml/models/nodemodel.h>

#include <QObject>
#include <jni.h>

class AndroidNotifier : public QObject
{
    Q_OBJECT

public:
    explicit AndroidNotifier(const NodeModel & node_model, QObject * parent = nullptr);

public Q_SLOTS:
    void onBlockTipHeightChanged();
    void onNumOutboundPeersChanged();
    void onVerificationProgressChanged();
    void onPausedChanged();

private:
    const NodeModel & m_node_model;
};

#endif // AIXCOIN_QML_ANDROIDNOTIFIER_H
