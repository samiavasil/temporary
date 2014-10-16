#include"FraDevice.h"
#include <string.h>
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

struct FraMeasurment_t{
   double   StartFrequency;
   double   StopFrequency;
   double   OutputCurrent;
   u32      NumberOfPoints;
   u32      TimeDelayMsec;
   MeasurementConfig::eScale_t ScaleType;
};


typedef struct {
   double    FrequencyScale;
   double    OutputCurrentScale;
} FraScales_t;

MeasurementConfig::MeasurementConfig(){
    m_Cfg = new FraMeasurment_t;
    memset( m_Cfg, 0, sizeof(m_Cfg[0]) );
}

MeasurementConfig::~MeasurementConfig(){
    delete m_Cfg;
}


double   MeasurementConfig::GetStartFrequencyUi(){
    return m_Cfg->StartFrequency;
}


void     MeasurementConfig::SetStartFrequencyUi( double& val ){
    m_Cfg->StartFrequency = val;
}


double   MeasurementConfig::GetStopFrequencyUi(){
    return m_Cfg->StopFrequency;
}


void     MeasurementConfig::SetStopFrequencyUi( double& val ){
    m_Cfg->StopFrequency = val;
}


double   MeasurementConfig::GetOutputCurrentUi(){
    return m_Cfg->OutputCurrent;
}


void     MeasurementConfig::SetOutputCurrentUi( double& val ){
    m_Cfg->OutputCurrent = val;
}


void     MeasurementConfig::SetNumberOfPoints( u32 num ){
    m_Cfg->NumberOfPoints = num;
}


u32      MeasurementConfig::GetNumberOfPoints(  ){
    return m_Cfg->NumberOfPoints;
}


void     MeasurementConfig::SetDelayMsec( u32 msec ){
      m_Cfg->TimeDelayMsec = msec;
}


u32      MeasurementConfig::GetDelayMsec(  ){
    return m_Cfg->TimeDelayMsec;
}


void     MeasurementConfig::SetScaleType(  MeasurementConfig::eScale_t type ){
    m_Cfg->ScaleType = type;
}


MeasurementConfig::eScale_t MeasurementConfig::GetScaleType(  ){
    return m_Cfg->ScaleType;
}

QDebug operator<<(  QDebug Ostr, const struct FraMeasurment_t* Cfg ){
    Ostr << "FraMeasurment_t structure:" << endl;
    Ostr << "\t" << "StartFrequency: " << Cfg->StartFrequency  << endl;
    Ostr << "\t" << "StopFrequency : " << Cfg->StopFrequency   << endl;
    Ostr << "\t" << "OutputCurrent : " << Cfg->OutputCurrent   << endl;
    Ostr << "\t" << "ScaleType     : " << Cfg->ScaleType       << endl;
    Ostr << "\t" << "NumberOfPoints: " << Cfg->NumberOfPoints  << endl;
    return Ostr;
}

void MeasurementConfig::DumpConfig()
{
    qDebug() <<  m_Cfg;
}

