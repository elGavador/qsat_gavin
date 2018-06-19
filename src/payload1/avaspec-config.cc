#include <sys/types.h>
#include <stdlib.h>
#include "avaspec.h"
#include "avaspec-configure.h"

void setAvaSpecParameters(MeasConfigType* a_pMeasConfig)
{
        a_pMeasConfig -> m_StartPixel                    = 0;
        
        a_pMeasConfig -> m_StopPixel                     = 2047;
        
        a_pMeasConfig -> m_IntegrationTime               = 100; // ms

        a_pMeasConfig -> m_IntegrationDelay              = 0;

        a_pMeasConfig -> m_NrAverages                    = 1;

        a_pMeasConfig -> m_CorDynDark.m_Enable           = 0;

        a_pMeasConfig -> m_CorDynDark.m_ForgetPercentage = 100;

        a_pMeasConfig -> m_Smoothing.m_SmoothPix         = 0;

        a_pMeasConfig -> m_Smoothing.m_SmoothModel       = 0;

        a_pMeasConfig -> m_Trigger.m_Mode                = 0;

        a_pMeasConfig -> m_Trigger.m_Source              = 0;

        a_pMeasConfig -> m_Trigger.m_SourceType          = 0;

        a_pMeasConfig -> m_Trigger.m_SourceType          = 0;

        a_pMeasConfig -> m_Control.m_StrobeControl       = 0;

        a_pMeasConfig -> m_Control.m_LaserDelay          = 0;

        a_pMeasConfig -> m_Control.m_LaserWidth          = 10000; // ns

        a_pMeasConfig -> m_Control.m_LaserWaveLength     = 785; // ns

        a_pMeasConfig -> m_Control.m_StoreToRam          = 5; 
}
