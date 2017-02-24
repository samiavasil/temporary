#include "base/CCommandExecutor.h"
#include "base/CCommand.h"

CCommandExecutor::CCommandExecutor() {
  m_CommandLoopTime = 10;
}

CCommandExecutor::~CCommandExecutor() {
}

int CCommandExecutor::appendCommand(CCommand *command) {
    int ret;
    lockObject();
    ret = appendCommand_internal(command);
    unlockObject();
    return ret;
}

void CCommandExecutor::flushCommands(){
    lockObject();
    flushCommands_internal();
    unlockObject();
}

int CCommandExecutor::getCommNum() {
    int count;
    lockObject();
    count = getCommNum_internal();
    unlockObject();
    return count;
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


void CCommandExecutor::timerHandlerExecuteAllCommands() {
    lockObject();
    for( int i = 0; i < getCommNum(); i++ ){
        if( 0 == executeCommand( i ) )
        {
            removeCommand(i);
            i--;
        }
    }
    if( 0 < getCommNum() ){
        startTimer( );
    }
    unlockObject();
}
