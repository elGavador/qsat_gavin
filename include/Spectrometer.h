#ifndef SRC_SPECTROMETER_H
#define SRC_SPECTROMETER_H

#include "avaspec.h"

class Spectrometer {

	private:

		MeasConfigType* a_pMeasConfig;

		AvsHandle a_hDevice;
		
		unsigned int* a_pTimeLabel;

    public:
			
        Spectrometer();

		double* buffer;

		void activate();

		void diactivate();

        void setMeasureConfig();

        void  measure();
};

#endif
