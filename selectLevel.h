#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SelectLevel; }
QT_END_NAMESPACE

class SelectLevel : public QWidget
{
    Q_OBJECT

public:
    explicit SelectLevel(QWidget *parent = nullptr);
    ~SelectLevel();

private:
    Ui::SelectLevel *ui;
};

#endif // SELECTLEVEL_H
