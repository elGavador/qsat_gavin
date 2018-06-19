UPDATED: 2017-12-3

OVERVIEW
    Header declerations for implementations of classes and functions found
    in /src/.

FILE STRUCTURE

    2 directories, 9 files
    .
    ├── README.txt
    ├── log.h
    └── spectrometer
        ├── AvaSpec
        │   ├── as5216.h
        │   ├── avaspec.h
        │   ├── extcode.h
        │   ├── testavs.pro
        │   └── type.h
        ├── Spectrometer.h
        └── avaspec-configure.h


DESCRIPTION
    /spectrometer
        /Avaspec
            Necessary interfaces to use spectrometer. Created by AvaSpec.
        /Spectrometer.h
            Spectrometer class used to activate, initialize and take
            measurement from spectrometer.
        /avaspec-configure.h
            Creates AvaSpec structure necessary to configure spectrometer 
            Configurations such as start pixel, stop pixel, integration
            time etc.
            
