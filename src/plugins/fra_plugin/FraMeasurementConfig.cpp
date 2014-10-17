#include"FraMeasurementConfig.h"
#include <string.h>
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

struct FraMeasurment_t{
   double   StartFrequency;
   double   StopFrequency;
   double   OutputCurrent;
   u32      NumberOfPoints;
   u32      TimeDelayMsec;
   FraMeasurementConfig::eScale_t ScaleType;
};


typedef struct {
   double    FrequencyScale;
   double    OutputCurrentScale;
} FraScales_t;

FraMeasurementConfig::FraMeasurementConfig(){
    m_Cfg = new FraMeasurment_t;
    memset( m_Cfg, 0, sizeof(m_Cfg[0]) );
}

FraMeasurementConfig::~FraMeasurementConfig(){
    delete m_Cfg;
}


double   FraMeasurementConfig::GetStartFrequencyUi(){
    return m_Cfg->StartFrequency;
}


void     FraMeasurementConfig::SetStartFrequencyUi( double& val ){
    m_Cfg->StartFrequency = val;
}


double   FraMeasurementConfig::GetStopFrequencyUi(){
    return m_Cfg->StopFrequency;
}


void     FraMeasurementConfig::SetStopFrequencyUi( double& val ){
    m_Cfg->StopFrequency = val;
}


double   FraMeasurementConfig::GetOutputCurrentUi(){
    return m_Cfg->OutputCurrent;
}


void     FraMeasurementConfig::SetOutputCurrentUi( double& val ){
    m_Cfg->OutputCurrent = val;
}


void     FraMeasurementConfig::SetNumberOfPoints( u32 num ){
    m_Cfg->NumberOfPoints = num;
}


u32      FraMeasurementConfig::GetNumberOfPoints(  ){
    return m_Cfg->NumberOfPoints;
}


void     FraMeasurementConfig::SetDelayMsec( u32 msec ){
      m_Cfg->TimeDelayMsec = msec;
}


u32      FraMeasurementConfig::GetDelayMsec(  ){
    return m_Cfg->TimeDelayMsec;
}


void     FraMeasurementConfig::SetScaleType(  FraMeasurementConfig::eScale_t type ){
    m_Cfg->ScaleType = type;
}


FraMeasurementConfig::eScale_t FraMeasurementConfig::GetScaleType(  ){
    return m_Cfg->ScaleType;
}

FraMeasurementConfig& FraMeasurementConfig::operator = (FraMeasurementConfig& obj){
    *(this->m_Cfg) = *(obj.m_Cfg);
}

QDebug operator<<(  QDebug Ostr, const struct FraMeasurment_t* Cfg ){
    Ostr << "FraMeasurment_t structure:" << endl;
    Ostr << "\t" << "StartFrequency: " << Cfg->StartFrequency  << endl;
    Ostr << "\t" << "StopFrequency : " << Cfg->StopFrequency   << endl;
    Ostr << "\t" << "OutputCurrent : " << Cfg->OutputCurrent   << endl;
    Ostr << "\t" << "ScaleType     : " << Cfg->ScaleType       << endl;
    Ostr << "\t" << "NumberOfPoints: " << Cfg->NumberOfPoints  << endl;
    Ostr << "\t" << "TimeDelayMsec: "  << Cfg->TimeDelayMsec   << endl;
    return Ostr;
}

void FraMeasurementConfig::DumpConfig()
{
    qDebug() <<  m_Cfg;
}

