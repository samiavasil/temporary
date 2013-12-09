#ifndef ODFWRITER_H
#define ODFWRITER_H
#include <QtGui>

class DocWriter
{
public:
    DocWriter();
    ~DocWriter();
    void write(const QString &fileName, QTextDocument * const document );
private:
    QTextDocument * const m_document;
    QTextCursor m_cursor;
};

#endif // ODFWRITER_H
