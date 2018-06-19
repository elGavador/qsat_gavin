TEMPLATE = app
HEADERS = avaspec.h 
SOURCES = testavs.cpp
unix:!macx {
	LIBS += -lavs
}
macx: {
	LIBS += -L/usr/local/lib -lavs
}
