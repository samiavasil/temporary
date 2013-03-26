#ifndef _CCREATOR_H
#define _CCREATOR_H


class CFrameWork;

class CCreator {
  public:
    virtual void Create( CFrameWork * fW) = 0;

    virtual void Free() = 0;

};
#endif
