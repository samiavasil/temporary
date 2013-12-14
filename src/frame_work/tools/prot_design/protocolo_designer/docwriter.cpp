#include "docwriter.h"
#include <QDebug>
//"odf"
#define TYPE "html"
DocWriter::DocWriter():m_document(new QTextDocument()),
    m_cursor(m_document)
{

}

DocWriter::~DocWriter()
{
    delete m_document;
}

void DocWriter::write(const QString &fileName, QTextDocument *const document)
{
    QTextDocumentWriter writer(fileName);
    qDebug() << writer.supportedDocumentFormats();
    writer.setFormat(TYPE);
    writer.write(document);
}

typedef enum
{
    NEXT_TABLE,
    NEXT_LIST
} move_type_t;

int move_cursor_to_next( QTextCursor& cursor, move_type_t type )
{
    int ret = 0;
    switch( type )
    {
    case NEXT_TABLE:
    {
        QTextTable * tb;

        while( cursor.currentTable() )
        {
            if(!cursor.movePosition(QTextCursor::NextBlock ))
            {
                break;
            }
        }

        while( cursor.movePosition(QTextCursor::NextBlock ) )
        {
            tb = cursor.currentTable();
            if( tb )
            {
                ret = 1;
                break;
            }

        }
        break;
    }
    case NEXT_LIST:
    {
        QTextList * list;

        if( cursor.currentList() )
        {
            cursor.movePosition(QTextCursor::NextBlock );
        }

        while( NULL == (list = cursor.currentList()) )
        {
            if( !cursor.movePosition(QTextCursor::NextBlock ) )
            {
                break;
            }

        }
        if( NULL != list )
        {
            ret = 1;
        }
        break;
    }
    }
    return ret;
}

int DocWriter::generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list ){
    // output_writer::generate_all(  pack_list,   msg_list);

    int ret = 0;
    QFile file( "com_des.html" );
    if( ! file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return -1;
    }
    QTextBrowser* textEdit = new QTextBrowser();
    QTextDocument *in_doc  = new QTextDocument();;
    QTextDocument *out_doc = new QTextDocument(textEdit);

    in_doc->setHtml( file.readAll() );
    //out_doc->setDocumentLayout(in_doc->documentLayout());
    QTextCursor   in_cursor(in_doc);
    QTextCursor   out_cursor(out_doc);
    QTextList *   listRimsko = NULL;
    QTextList *   list_arab  = NULL;
    QTextTable *  msg_tb     = NULL;
    QTextTable *  pack1_tb     = NULL;
    QTextTable *  pack2_tb     = NULL;


    textEdit->setDocument( out_doc );
    textEdit->show();
    QTextBlockFormat def_bformat  = in_cursor.block().blockFormat();
    QTextCharFormat  def_chformat = in_cursor.block().charFormat();

    if( move_cursor_to_next( in_cursor , NEXT_LIST ) )
    {
        listRimsko = in_cursor.currentList();
        if( NULL == listRimsko )
        {
            ret = -1;
            goto ERR;
        }
        qDebug()<< "List Rimski: " << in_cursor.block().text();

        if( move_cursor_to_next( in_cursor , NEXT_LIST ) )
        {
            list_arab = in_cursor.currentList();
            if( NULL == list_arab )
            {
                ret = -1;
                goto ERR;
            }
            qDebug()<< "List Arabski: " << in_cursor.block().text();
            if( move_cursor_to_next( in_cursor , NEXT_TABLE ) )
            {
                msg_tb   = in_cursor.currentTable();
                if( NULL == msg_tb )
                {
                    ret = -1;
                    goto ERR;
                }
                qDebug()<< "TABLE MESSAGES: " << in_cursor.block().text();
                if( move_cursor_to_next( in_cursor , NEXT_TABLE ) )
                {
                    pack1_tb   = in_cursor.currentTable();
                    if( NULL == pack1_tb )
                    {
                        ret = -1;
                        goto ERR;
                    }
                    qDebug()<< "TABLE PACK1: " << in_cursor.block().text();
                    if( move_cursor_to_next( in_cursor , NEXT_TABLE ) )
                    {
                        pack2_tb   = in_cursor.currentTable();
                        if( NULL == pack2_tb )
                        {
                            ret = -1;
                            goto ERR;
                        }
                        qDebug()<< "TABLE PACK2: " << in_cursor.block().text();

                    }
                }
            }

            QTextTable * tb;
            QMapIterator< int, msg_types_t > it(msg_list);
            QTextList *   t_list_arab;

            QTextTableFormat table_format;
            table_format.setCellPadding (5);

            QVector <QTextLength> col_widths;
            for (int i = 0; i < msg_tb->columns(); ++i)
                col_widths << QTextLength (QTextLength::PercentageLength, 100.0 / msg_tb->columns());

            table_format.setColumnWidthConstraints (col_widths);

            for( int i=0; i< msg_list.count() ;i ++ )
            {
                it.next();
                if(  i == 0 )
                {
                    out_cursor.insertList( list_arab->format() );
                    t_list_arab = out_cursor.currentList();
                    if( NULL == t_list_arab )
                    {
                        ret =-1;
                        goto ERR;
                    }

                }
                else
                {
                    t_list_arab->add(out_cursor.block());
                }
                out_cursor.setBlockFormat(list_arab->item(0).blockFormat());
                out_cursor.setCharFormat(list_arab->item(0).charFormat());
                out_cursor.setBlockCharFormat(list_arab->item(0).charFormat());
                out_cursor.insertText( "Message Name " + it.value().msgName );


                out_cursor.insertBlock();
                out_cursor.setBlockFormat( def_bformat );
                out_cursor.setBlockCharFormat( def_chformat );
                out_cursor.setCharFormat( def_chformat );

                if( out_cursor.insertTable( msg_tb->rows(), msg_tb->columns(), table_format ) )
                {
                    tb   = out_cursor.currentTable();
                    tb->setFormat ( msg_tb->format() );

                    for( int j=0; j < tb->columns();j++ )
                    {
                        for( int k=0; k < tb->rows();k++ )
                        {
                            tb->cellAt(k,j).setFormat( msg_tb->cellAt(k,j).format() );
                            if( k == 0 )
                            {
                                tb->cellAt(k,j).firstCursorPosition().insertText( msg_tb->cellAt(k,j).firstCursorPosition().block().text() );
                            }
                        }
                    }

                    out_cursor.movePosition( QTextCursor::NextRow );
                    out_cursor.insertText(  it.value().msgName );
                    if(!out_cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 1;
                    }
                    out_cursor.insertText(  QString("%1").arg(it.value().BitLen) );
                    if(!out_cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 2;
                    }
                    out_cursor.insertText(  QString("%1").arg(it.value().Type) );
                    if(!out_cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 2;
                    }
                    out_cursor.insertText(  QString("%1").arg(it.value().DefaultValue) );

                    if(!out_cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 2;
                    }
                    out_cursor.insertText(  it.value().msgDescription );
                    //
                    //                    out_cursor.insertText( "\n\n\n" );


                    if( !it.hasNext() )
                    {
                        break;
                    }
                    else
                    {
                        out_cursor.movePosition( QTextCursor::NextBlock );
                        out_cursor.setBlockFormat( def_bformat );
                        out_cursor.setBlockCharFormat( def_chformat );
                        out_cursor.setCharFormat( def_chformat );
                        out_cursor.insertText( "\n\n" );
                    }
                }
            }
              write( "test."TYPE, out_doc );
            }
        }
        //out_doc->deleteLater();
ERR:
        in_doc->deleteLater();
        return ret;
}
