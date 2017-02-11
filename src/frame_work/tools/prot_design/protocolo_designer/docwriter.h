#ifndef ODFWRITER_H
#define ODFWRITER_H
#include <QtGui>
#include "output_writer.h"

class DocWriter:public output_writer
{
public:
    DocWriter();
    ~DocWriter();
    void write(const QString &fileName, QTextDocument * const document );
    int build_doc(const ComMatrix &matrix);
protected:
    void populateDocument(QTextDocument *document, const QString &title, const ComMatrix &matrix);
    void addMessagesToDocument(QTextCursor *cursor, const ComMatrix &matrix);
    void addPacketsToDocument(QTextCursor *cursor, const ComMatrix &matrix);
    void addTitleToDocument(QTextCursor *cursor, const QString &title);
    void addItemsToDocument(QTextCursor *cursor, const ComMatrix &matrix);
    void addTableToDocument(QTextCursor *cursor, const QList<QPair<QString, QList<QString> > > &pairs);
private:
    QTextDocument * const m_document;
    QTextCursor m_cursor;
};

#endif // ODFWRITER_H

