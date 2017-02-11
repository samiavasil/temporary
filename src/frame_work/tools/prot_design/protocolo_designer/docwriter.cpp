#include "docwriter.h"
#include <QDebug>
#include <QTextBrowser>
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

    QBuffer*  buffer = new QBuffer();

    QTextDocumentWriter writer_str( buffer, TYPE );

    writer_str.write(document);

    if( buffer->open(QBuffer::ReadWrite) )
    {
        document->setHtml(  buffer->readAll() );
        writer.setFormat(TYPE);
        writer.write(document);
    }

}

typedef enum
{
    NEXT_BLOCK,
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


void DocWriter::addTitleToDocument( QTextCursor* cursor, const QString &title )
{
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignHCenter);
    blockFormat.setTopMargin(0);
    cursor->insertBlock(blockFormat);
    QTextCharFormat charFormat;
    charFormat.setFont(QFont("Helvetica", 24, QFont::Bold));
    cursor->insertText(title, charFormat);
    cursor->movePosition(QTextCursor::End);
}

#if 0
void DocWriter::populateTableCell(QTextTableCell tableCell, const OnePage &thePage, int index)
{
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignHCenter);
    QTextCursor cursor = tableCell.firstCursorPosition();
    cursor.insertBlock(blockFormat);
    cursor.insertImage(thePage.filenames.at(index));
    blockFormat.setTopMargin(30);
    cursor.insertBlock(blockFormat);
    QTextCharFormat charFormat;
    charFormat.setFont(QFont("Helvetica", 18));
    cursor.insertText(thePage.captions.at(index), charFormat);
}
#endif


void DocWriter::addTableToDocument( QTextCursor* cursor, const QList< QPair<QString,QList<QString>> >& pairs )
{
    if( cursor && pairs.count() > 0)
    {
        QTextDocument listDocumment;
        QTextCursor listCursor(&listDocumment);
        QTextFrame* MainFrame = listCursor.currentFrame();
        QTextFrameFormat format;
        format.setTopMargin( 20 );
        format.setLeftMargin( 100 );//TODO!!!
        listCursor.insertFrame(format);
        QTextTableFormat tableFormat;
        tableFormat.setBackground(QColor("#ffe0e0"));
        QVector<QTextLength> constraints;
        int per = (100 - 40)/pairs.count();
        for( int i=0; i < pairs.count();i++ )
        {
            if( i < pairs.count() - 1 )
            {
                constraints << QTextLength(QTextLength::PercentageLength, per);
            }
            else
            {
                constraints << QTextLength(QTextLength::PercentageLength, 40);
            }
        }
        tableFormat.setColumnWidthConstraints(constraints);
        QTextTable *table = listCursor.insertTable( pairs[0].second.count() + 1, pairs.count(), tableFormat );
        QTextTableCell cell;
        QTextCursor cellCursor;
        for (int column = 0; column < table->columns(); ++column) {
            for (int row = 0; row < table->rows(); ++row) {
                cell = table->cellAt( row, column );
                cellCursor = cell.firstCursorPosition();
                if( row == 0 )
                {
                    QTextCharFormat fm = cell.format();
                    fm.setBackground(QColor("#e0e0e0"));
                    cell.setFormat(fm);
                    cellCursor.insertText( pairs[column].first );//TODO , charFormat);
                }
                else
                {
                    cellCursor.insertText( pairs[column].second[row-1] );//TODO , charFormat);
                }
            }
        }
        listCursor = MainFrame->lastCursorPosition();
        cursor->insertFragment(QTextDocumentFragment(&listDocumment));
    }
}

void DocWriter::addMessagesToDocument( QTextCursor* cursor, const ComMatrix &matrix )
{
    QList< QPair<QString,QList<QString>> > pairs;
    if( matrix.getMsgPairs( pairs ) )
    {
        addTableToDocument( cursor, pairs );
    }
}

void DocWriter::addPacketsToDocument( QTextCursor* cursor, const ComMatrix &matrix )
{
    QList< QPair<QString,QList<QString>> > pairs;
    foreach( auto pkgId, matrix.packetsList().keys() ) {
        if( matrix.getPkgPairs( pkgId, pairs ) )
        {
            addTableToDocument( cursor, pairs );
        }
        pairs.clear();
    }
    cursor->movePosition(QTextCursor::End);
}

void DocWriter::addItemsToDocument( QTextCursor* cursor, const ComMatrix &matrix )
{
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignLeft);
    QTextCharFormat charFormat;
    charFormat.setFont( cursor->document()->defaultFont() );

    cursor->insertBlock( blockFormat );
    QTextList* list =  cursor->insertList( QTextListFormat::ListUpperRoman );
    cursor->insertText(QString("Messages"), charFormat );
    addMessagesToDocument( cursor, matrix );
    cursor->insertBlock(blockFormat);
    list->add(cursor->block());
    cursor->insertText(QString("Packets"));
    addPacketsToDocument( cursor, matrix );
}

void DocWriter::populateDocument( QTextDocument *  document,const QString& title, const ComMatrix &matrix )
{
    document->setDefaultFont(QFont("Times", 15));
    QTextCursor cursor(document);
    addTitleToDocument( &cursor, title );
    addItemsToDocument( &cursor, matrix );
}


int DocWriter::build_doc(const ComMatrix &matrix )
{
    QTextDocument *document  = new QTextDocument();
    if( document )
    {
        QTextBrowser* textEdit = new QTextBrowser();//QTextEdit
        populateDocument( document,"COMMUNICTAION MATRIX", matrix );
        textEdit->resize(1000,800);
        textEdit->setDocument( document );
        textEdit->show();
        //   document->deleteLater();
    }
}
