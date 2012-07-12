
#include "base/CFrameWork.h"
#include "base/CControlView.h"
#include "base/CDataPlot.h"
#include "base/CCommandExecutor.h"
#include "base/CProtocolPackFactory.h"
#include "base/CPortIO.h"
#include "base/CPacketCollector.h"

CPortIO * CFrameWork::getPortIO() {
  return mPortIO;
}

CPacketCollector  * CFrameWork::getColector() volatile {
  return m_Colector;
}

CProtocolPackFactory * CFrameWork::getProtocol() {
  return m_Protocol;
}

CCommandExecutor* CFrameWork::geExecutor() {
  return m_Executor;
}

CDataPlot * CFrameWork::getDataPlot() {
  return m_DataPlot;
}

CControlView* CFrameWork::getControlView() {
  return m_ControlView;
}

