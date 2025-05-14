#include <QClipboard>
#include <QContextMenuEvent>
#include <QGuiApplication>
#include <QLabel>
#include <QMenu>

namespace kaptisto
{

class CopyableLabel : public QLabel
{
    Q_OBJECT
  public:
    explicit CopyableLabel(QWidget *parent = nullptr) : QLabel(parent)
    {
    }

    explicit CopyableLabel(QString text, QWidget *parent = nullptr) : QLabel(text, parent)
    {
    }

  protected:
    void contextMenuEvent(QContextMenuEvent *event) override
    {
        QMenu menu(this);
        QAction *copyAction = menu.addAction("复制到剪贴板");
        QAction *selectedAction = menu.exec(event->globalPos());

        if (selectedAction == copyAction)
        {
            auto &&pix = this->pixmap();
            if (!pix.isNull())
            {
                QGuiApplication::clipboard()->setPixmap(pix);
                qDebug() << "已复制图片到剪贴板";
            }
        }
    }
};

} // namespace kaptisto
