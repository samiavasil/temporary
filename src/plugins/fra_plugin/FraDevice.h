#ifndef FRADEVICE_H
#define FRADEVICE_H
#include "base/global.h"



class MeasurementConfig{
public:
    typedef enum{
        E_LINEAR,
        E_LOGARITMIC
    }eScale_t;
public:
    MeasurementConfig();
    ~MeasurementConfig();
    double   GetStartFrequencyUi();
    void     SetStartFrequencyUi( double& val );
    double   GetStopFrequencyUi();
    void     SetStopFrequencyUi( double& val );
    double   GetOutputCurrentUi();
    void     SetOutputCurrentUi( double& val );
    void     SetNumberOfPoints( u32 num );
    u32      GetNumberOfPoints(  );
    void     SetDelayMsec( u32 msec );
    u32      GetDelayMsec(  );
    void     SetScaleType(  MeasurementConfig::eScale_t type );
    eScale_t GetScaleType(  );
    void     DumpConfig();
//friend QDebug& operator << (QDebug& deb , const struct FraMeasurment_t& cfg);
protected:
    struct FraMeasurment_t* m_Cfg;
};
//QDebug &operator <<(QDebug& deb, const FraMeasurment_t* cfg);
#endif // FRADEVICE_H
