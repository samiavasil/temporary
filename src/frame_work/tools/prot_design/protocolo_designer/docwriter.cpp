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
        while( cursor.movePosition(QTextCursor::NextBlock ) )
        {
            list = cursor.currentList();
            if( list )
            {
                ret = 1;
                break;
            }

        }
        break;
    }
    }
    return ret;
}

int DocWriter::generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list ){
    // output_writer::generate_all(  pack_list,   msg_list);


    QFile file( "com_des.html" );
    if( ! file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return -1;
    }
    QTextBrowser* textEdit = new QTextBrowser();
    textEdit->setAcceptRichText ( true );
    // textEdit->setAutoFormatting ( QTextEdit::AutoNone );
    textEdit->setHtml( file.readAll() );
    // textEdit->setSource ( QUrl("com_des.html") );

    QTextDocument *doc =textEdit->document();
    QTextCursor cursor(doc);
    qDebug()<< cursor.atBlockStart() <<textEdit->autoFormatting() << textEdit->acceptRichText() << textEdit->accessibleDescription();

    textEdit->setLineWrapMode ( QTextBrowser::WidgetWidth );
    textEdit->setLineWrapColumnOrWidth ( 1000 );

    textEdit->show();

    if( move_cursor_to_next( cursor , NEXT_LIST ) )
    {
        QTextList * listRimsko = cursor.currentList();
        if( NULL == listRimsko )
        {
            return -1;
        }

        if( move_cursor_to_next( cursor , NEXT_LIST ) )
        {
            QTextList * list = cursor.currentList();
            if( NULL == list )
            {
                return -1;
            }
            qDebug() << " LISTA:\n";
            for( int i=0; i < list->count(); i++ )
            {
                qDebug() << list->itemText(list->item( i ));
            }
            qDebug()<< cursor.block().text();
            cursor.movePosition( QTextCursor::NextCharacter );
            cursor.select( QTextCursor::LineUnderCursor );
            QTextCharFormat chf = cursor.blockCharFormat();
           /// cursor.removeSelectedText();
            cursor.insertText( "WWWW" );
            cursor.setBlockCharFormat(chf);
            if( move_cursor_to_next( cursor , NEXT_TABLE ) )
            {
                QTextTable * tb  = cursor.currentTable();
                cursor.movePosition( QTextCursor::NextRow );
                QMapIterator< int, msg_types_t > it(msg_list);

                tb->insertRows( tb->rows(),msg_list.count() - 1 );
                for( int i=0; i< msg_list.count() ;i ++ )
                {
                    it.next();
                    cursor.insertText(  it.value().msgName );
                    if(!cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 1;
                    }
                    cursor.insertText(  QString("%1").arg(it.value().BitLen) );
                    if(!cursor.movePosition( QTextCursor::NextCell ))
                    {
                        qDebug()<<"Can't move to next cell: " << i << "," << 2;
                    }
                    cursor.insertText(  it.value().msgDescription );
                    if( !it.hasNext() )
                    {
                        break;
                    }

                    if(!cursor.movePosition( QTextCursor::NextRow ))
                    {
                        qDebug()<<"Can't move to next row: " << i+1;
                    }

                }
                cursor.movePosition( QTextCursor::End );
                QTextTable* table = cursor.insertTable( 1, tb->columns(), tb->format() );
                for( int j=0; j < tb->columns();j++ )
                {
                    table->cellAt(0,j).setFormat( tb->cellAt(0,j).format() );
                }
                for( int i=0; i< 5 ;i ++ )
                {
                    table->appendRows(1);
                    cursor.movePosition( QTextCursor::NextRow ) ;
                    for( int j=0; j < tb->columns();j++ )
                    {

                        cursor.insertText( QString("i=%1 j=%2").arg(i).arg(j) );
                        if( j < tb->columns()-1 )
                        {
                            if( !cursor.movePosition( QTextCursor::NextCell ) )
                            {
                                qDebug()<<"Can't move to next cell: " << i << "," << j;
                            }
                        }
                    }
                }
            }
        }


    }
    write( "test."TYPE, textEdit->document() );
    textEdit->show();
    return 0;
}
