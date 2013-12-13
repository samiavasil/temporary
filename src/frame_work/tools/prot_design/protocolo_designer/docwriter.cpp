#include "docwriter.h"
#include <QDebug>
//"odf"
#define TYPE "html"
DocWriter::DocWriter():m_document(new QTextDocument()),
    m_cursor(m_document)
{

    QFile file( "com_des.html" );
    if( ! file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return;
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
    //
    QTextTable * tb;
    while( cursor.movePosition(QTextCursor::NextWord ) )
    {
        tb = cursor.currentTable();
        if( tb )
        {
            for( int i=0; i< 5 ;i ++ )
            {
                tb->appendRows(1);
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
            break;
        }

    }
    cursor.movePosition(QTextCursor::End );
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


    write( "test."TYPE, textEdit->document() );
      textEdit->show();

    return;
    QList<QTextList *> List;
    QTextFrameFormat frame_format;
    QTextCharFormat char_format;
    QTextBlockFormat bl_format;
    frame_format.setBorder(5);
    frame_format.setBackground(QBrush(QColor(0,((qrand())%255),121)));
    frame_format.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    for(int j=0;j<5;j++)
    {
        //m_cursor.insertFrame(frame_format);
        List.append(m_cursor.insertList( QTextListFormat::ListDisc ));
        bl_format.setLayoutDirection(Qt::RightToLeft);
        m_cursor.insertBlock(bl_format);

        char_format.setFontPointSize( (qrand()%36)+10);
        m_cursor.insertText( QString("Table Pacet Message Map %1").arg(j),char_format );

        //m_cursor.insertText( QString("BLIAK") );

        QTextTableFormat tableFormat;
        tableFormat.setCellPadding(5);

        tableFormat.setHeaderRowCount(1);
        tableFormat.setBorderBrush(QBrush(QColor(255,0,255)));
        tableFormat.setBorder(10);
        tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Inset);
        tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

        QTextTable* table = m_cursor.insertTable(1, 3, tableFormat);
        m_cursor.insertText("Date");

        m_cursor.movePosition(QTextCursor::NextCell);
        m_cursor.insertText("Duration (sec)");
        m_cursor.movePosition(QTextCursor::NextCell);
        m_cursor.insertText("Cost");
        m_cursor.insertList( QTextListFormat::ListCircle );
        m_cursor.insertText("1000\n");
        m_cursor.insertText("200\n");
        m_cursor.insertText("300");
        for(int i=0;i< 10;i++)
        {
            table->appendRows(1); // moves our cursor to the end of the doc...
            m_cursor.movePosition(QTextCursor::PreviousRow);
            m_cursor.movePosition(QTextCursor::NextCell);
            m_cursor.insertText(QDate::fromJulianDay ( qrand() ).toString());
            m_cursor.movePosition(QTextCursor::NextCell);
            m_cursor.insertText(QString::number(qrand()));
            m_cursor.movePosition(QTextCursor::NextCell);
            m_cursor.insertText(QString::number(qrand()));
        }
        m_cursor.movePosition(QTextCursor::End );


    }
    write( "test."TYPE, m_document );
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

int DocWriter::generate_all( QMap< int, pack_types_t >& pack_list, QMap< int, msg_types_t  > & msg_list ){
         output_writer::generate_all(  pack_list,   msg_list);

}
