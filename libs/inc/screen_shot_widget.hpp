#pragma once

#include "copyable_label.hpp"
#include <QClipboard>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace kaptisto
{

class ScreenshotWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit ScreenshotWidget(QWidget *parent = nullptr)
        : QWidget(parent), btn_(new QPushButton("截图", this)),
          preview_(new CopyableLabel("点击截图按钮", this))
    {
        auto *layout = new QVBoxLayout(this);
        layout->addWidget(btn_);
        layout->addWidget(preview_);
        setLayout(layout);
        connect(btn_, &QPushButton::clicked, this, &ScreenshotWidget::onTakeScreenshot);
    }

  private slots:
    void onTakeScreenshot()
    {
        QDBusInterface iface("org.freedesktop.portal.Desktop",    // destination
                             "/org/freedesktop/portal/desktop",   // object path
                             "org.freedesktop.portal.Screenshot", // interface
                             QDBusConnection::sessionBus());

        // 参数 1: handle_token "{}"
        // 参数 2: options "{'interactive': <true>}"
        QString handle =
            QStringLiteral("qt-screenshot-%1").arg(QDateTime::currentMSecsSinceEpoch());
        QVariantMap options;
        options["interactive"] = true; // false 会失败，必须得交互，否则没有权限

        QDBusPendingCall call = iface.asyncCall("Screenshot", handle, options);

        auto *watcher = new QDBusPendingCallWatcher(call, this);
        connect(watcher, &QDBusPendingCallWatcher::finished, this,
                [this](QDBusPendingCallWatcher *w) {
                    QDBusPendingReply<QDBusObjectPath> reply = *w;
                    if (reply.isError())
                    {
                        qWarning()
                            << "Failed to call Screenshot:" << reply.error().message();
                    }
                    else
                    {
                        QString path = reply.value().path();
                        qDebug() << "Screenshot request path:" << path;

                        // 监听返回结果
                        QDBusConnection::sessionBus().connect(
                            "org.freedesktop.portal.Desktop", // sender
                            path,                             // object path
                            "org.freedesktop.portal.Request", // interface
                            "Response",                       // signal
                            this, SLOT(handleScreenshotResponse(uint, QVariantMap)));
                    }
                    w->deleteLater();
                });
    }

    void handleScreenshotResponse(uint code, const QVariantMap &results)
    {
        if (code != 0)
        {
            qWarning() << "Screenshot failed with code:" << code;
            return;
        }

        QString uri = results.value("uri").toString();
        qDebug() << "Screenshot saved to:" << uri;

        QUrl url(uri);
        QString localPath = url.toLocalFile();
        QPixmap pix(localPath);

        preview_->clear();
        if (pix.isNull())
        {
            preview_->setText("无法加载截图");
        }
        else
        {
            preview_->resize(pix.size());
            preview_->setPixmap(pix);
            preview_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            preview_->adjustSize();

            // 替换文件名中的空格为下划线（直接操作路径字符串）
            QString newPath = localPath;
            newPath.replace(" ", "_"); // 注意不是 %20，而是解码后的空格

            if (localPath != newPath)
            {
                if (pix.save(newPath))
                {
                    QFile::remove(localPath); // 删除原始带空格文件
                    qDebug() << "已保存截图到:" << newPath;
                }
                else
                {
                    qWarning() << "保存截图到新路径失败:" << newPath;
                }
            }
            else
            {
                qDebug() << "文件路径无空格，无需重命名";
            }
        }
    }

  private:
    QPushButton *btn_;
    CopyableLabel *preview_;
};

} // namespace kaptisto
