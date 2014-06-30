#ifndef QPLUGINVIEW_H
#define QPLUGINVIEW_H

#include <QWidget>
#include "qt/PluginDescription.h"
#include "qt/QPluginListWidget.h"

namespace Ui {
class QPluginSelectionView;
}

class QPluginSelectionView : public QWidget
{
    Q_OBJECT

public:
    explicit QPluginSelectionView(QWidget *parent = 0, const QpluginFilter& filter = QpluginFilter(),
                                  const cfgViewTypeT& viewType = cfgViewTypeT()  );
    ~QPluginSelectionView();
    const PluginDescription getSelectedPlugin();
protected slots:
    void selectedPluginChanged(const PluginDescription &desc);
private:
    Ui::QPluginSelectionView *ui;
signals:
    void ok_selected();
    void cancel_selected();
protected:
    QPluginListWidget m_wd;
};

#endif // QPLUGINVIEW_H
