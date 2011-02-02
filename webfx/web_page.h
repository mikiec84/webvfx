// Copyright (c) 2011 Hewlett-Packard Development Company, L.P. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBFX_WEB_PAGE_H_
#define WEBFX_WEB_PAGE_H_

#include <QWebPage>

class QEventLoop;
class QImage;
class QWebFrame;

namespace WebFX
{

class WebImage;
class WebParameters;
class WebRenderer;
class WebScript;

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    WebPage(WebRenderer* parent, WebParameters* parameters);
    ~WebPage();

    // Load URL synchronously, return success
    bool loadSync(const QUrl& url);
    WebImage render(double time);

private slots:
    void injectWebScript();
    bool shouldInterruptJavaScript();
    void webPageLoadFinished(bool result);
    void webScriptLoadFinished(bool result);

protected:
    void javaScriptAlert(QWebFrame* originatingFrame, const QString& msg);
    void javaScriptConsoleMessage(const QString& message, int lineNumber, const QString& sourceID);
    bool acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type);

private:
    enum LoadStatus { LoadNotFinished, LoadFailed, LoadSucceeded };
    LoadStatus pageLoadFinished;
    LoadStatus scriptLoadFinished;
    WebScript* webScript;
    QEventLoop* syncLoop;
    QImage* renderImage;
};

}

#endif
