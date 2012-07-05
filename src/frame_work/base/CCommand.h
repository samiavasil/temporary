#ifndef _CCOMMAND_H
#define _CCOMMAND_H


class CCommand {
  public:
    /**
     * Command handler
     */
    virtual int handler() const = 0;

};
#endif
