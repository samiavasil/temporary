#ifndef ODFWRITER_H
#define ODFWRITER_H
#include <QtGui>

class DocWriter
{
public:
    DocWriter();
    ~DocWriter();
    void write(const QString &fileName);
private:
    QTextDocument * const m_document;
    QTextCursor m_cursor;
};

#endif // ODFWRITER_H
