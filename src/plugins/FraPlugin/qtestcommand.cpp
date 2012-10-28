#include "qtestcommand.h"

QtestCommand::QtestCommand(QFrameWork * fWork) {
  m_fWork = fWork;
  a=0;
  DEBUG("QtestCommand Created");
}

QtestCommand::~QtestCommand() {
  DEBUG("QtestCommand Deleted");
}
