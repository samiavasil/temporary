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
    virtual int generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list );
private:
    QTextDocument * const m_document;
    QTextCursor m_cursor;
};

#endif // ODFWRITER_H

