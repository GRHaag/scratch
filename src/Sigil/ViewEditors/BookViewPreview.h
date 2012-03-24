/************************************************************************
**
**  Copyright (C) 2012 John Schember <john@nachtimwald.com>
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#ifndef BOOKVIEWPREVIEW_H
#define BOOKVIEWPREVIEW_H

#include <QtWebKit/QWebView>

#include <ViewEditors/Zoomable.h>

class QSize;

class BookViewPreview : public QWebView, public Zoomable
{
    Q_OBJECT

public:
    /**
     * Constructor.
     *
     * @param parent The object's parent.
     */
    BookViewPreview(QWidget *parent=0);

    QSize sizeHint() const;

    void CustomSetDocument(const QString &path, const QString &html);

    bool IsLoadingFinished();

    void SetZoomFactor(float factor);

    float GetZoomFactor() const;

    void Zoom();

    void UpdateDisplay();

    /**
     * Scrolls the editor to the top.
     */
    void ScrollToTop();

    /**
     * Scrolls the editor to the specified fragment.
     *
     * @param fragment The fragment ID to scroll to.
     *                 It should have the "#" character as the first character.
     */
    void ScrollToFragment(const QString &fragment);

    /**
     * Scrolls the editor to the specified fragment after the document is loaded.
     *
     * @param fragment The fragment ID to scroll to.
     *                 It should have the "#" character as the first character.
     */
    void ScrollToFragmentAfterLoad(const QString &fragment);

signals:
    /**
     * Emitted whenever the zoom factor changes.
     *
     * @param new_zoom_factor The new zoom factor of the View.
     */
    void ZoomFactorChanged(float new_zoom_factor);

    /**
     * A filtered version of the QWebPage::linkClicked signal.
     * Should be used in place of that one, since this one
     * performs custom logic on the QUrl.
     *
     * @param url The URL of the clicked link.
     */
    void FilteredLinkClicked(const QUrl& url);

    /**
     * Emitted when the focus is gained.
     */
    void FocusGained(QWidget* editor);

protected:
    /**
     * Handles the focus in event for the editor.
     *
     * @param event The event to process.
     */
    void focusInEvent(QFocusEvent *event);

    /**
     * Evaluates the provided javascript source code
     * and returns the result.
     *
     * @param javascript The JavaScript source code to execute.
     * @return The result from the last executed javascript statement.
     */
    QVariant EvaluateJavascript(const QString &javascript);

    bool m_isLoadFinished;

private slots:
    /**
     * Tracks the loading progress.
     * Updates the state of the m_isLoadFinished variable
     * depending on the received loading progress; if the
     * progress equals 100, the state is true, otherwise false.
     *
     * @param progress The value of the loading progress (0-100).
     */
    void UpdateFinishedState(int progress);

    /**
     * Filters the linkCLicked signal.
     *
     * @param url The URL of the clicked link.
     */
    void LinkClickedFilter(const QUrl& url);

private:
    float m_CurrentZoomFactor;
};

#endif // BOOKVIEWPREVIEW_H