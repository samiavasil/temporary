#include "base/CCommandExecutor.h"
#include "base/CCommand.h"

CCommandExecutor::CCommandExecutor() {
  m_CommandLoopTime = 10;
}

CCommandExecutor::~CCommandExecutor() {
}

/**
 * Set command loop time
 */
void CCommandExecutor::setCommandLoopTime(int time_ms) {
  m_CommandLoopTime = time_ms;
}

/**
 * Return command loop time [ms]
 */
int CCommandExecutor::getCommandLoopTime() {
  return m_CommandLoopTime;
}

