#ifndef FRAMEASURMENT_CONFIG_H
#define FRAMEASURMENT_CONFIG_H
#include "base/global.h"



class FraMeasurementConfig{
public:
    typedef enum{
        E_LINEAR,
        E_LOGARITMIC
    }eScale_t;
public:
    FraMeasurementConfig();
    ~FraMeasurementConfig();
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
    void     SetScaleType(  FraMeasurementConfig::eScale_t type );
    eScale_t GetScaleType(  );
    void     DumpConfig();
    FraMeasurementConfig& operator = (FraMeasurementConfig& obj);
protected:
    struct FraMeasurment_t* m_Cfg;
};
//QDebug &operator <<(QDebug& deb, const FraMeasurment_t* cfg);
#endif // FRADEVICE_H
