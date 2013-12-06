#include "docwriter.h"

#if 0
m_cursor.insertText(QString("Phone bill for %1\n").arg(clientName));

QTextTableFormat tableFormat;
tableFormat.setCellPadding(5);
tableFormat.setHeaderRowCount(1);
tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
m_cursor.insertTable(1, 3, tableFormat);
m_cursor.insertText("Date");
m_cursor.movePosition(QTextCursor::NextCell);
m_cursor.insertText("Duration (sec)");
m_cursor.movePosition(QTextCursor::NextCell);
m_cursor.insertText("Cost");
}

PhoneBillWriter::~PhoneBillWriter()
{
    delete m_document;
}

void PhoneBillWriter::addPhoneCall(const PhoneBillWriter::PhoneCall &call)
{
    QTextTable *table = m_cursor.currentTable();
    if (! table)
        return;

    table->appendRows(1); // moves our cursor to the end of the doc...
    m_cursor.movePosition(QTextCursor::PreviousRow);
    m_cursor.movePosition(QTextCursor::NextCell);
    m_cursor.insertText(call.date.toString());
    m_cursor.movePosition(QTextCursor::NextCell);
    m_cursor.insertText(QString::number(call.duration));
    m_cursor.movePosition(QTextCursor::NextCell);

    QChar euro(0x20ac);
    m_cursor.insertText(QString("%1 %2").arg(euro).arg(call.cost / (double) 100, 0, 'f', 2));
}

void PhoneBillWriter::addPastUsageGraph(QList<int> values, const QString &subtext)
{
    const int columnSize = 10;
    int width = values.count() * columnSize;
    int max = 0;
    foreach (int x, values)
        max = qMax(max, x);
    QImage image(width, 100, QImage::Format_Mono);
    QPainter painter(&image);
    painter.fillRect(0, 0, image.width(), image.height(), Qt::white); // background
    for (int index = 0; index < values.count(); ++index) {
        int height = values[index] * 100 / max; // adjust scale to our 100 pixel tall image
        painter.fillRect(index * columnSize, image.height() - height, columnSize, height, Qt::black);
    }
    painter.end();

    QTextCursor cursor(m_document);
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(subtext);
    cursor.insertBlock();
    cursor.insertImage(image);
}

void PhoneBillWriter::write(const QString &fileName)
{
    QTextDocumentWriter writer(fileName);
    writer.write(m_document);
}

#endif
#include <QDebug>
//"odf"
#define TYPE "html"
DocWriter::DocWriter():m_document(new QTextDocument()),
    m_cursor(m_document)
{
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
    write( "test."TYPE );
}

DocWriter::~DocWriter()
{
    delete m_document;
}

void DocWriter::write(const QString &fileName)
{
    QTextDocumentWriter writer(fileName);
    qDebug() << writer.supportedDocumentFormats();
    writer.setFormat(TYPE);
    writer.write(m_document);
}
