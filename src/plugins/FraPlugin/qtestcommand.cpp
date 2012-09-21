#include "qtestcommand.h"

QtestCommand::QtestCommand(QFrameWork * fWork) {
  m_fWork = fWork;
  a=0;
  qDebug("QtestCommand Created");
}

QtestCommand::~QtestCommand() {
  qDebug("QtestCommand Deleted");
}
