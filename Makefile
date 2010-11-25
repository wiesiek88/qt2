QMAKE=/usr/bin/qmake
MAKEFILE=Makefile
VIEWER_PRO=qute_viewer.pro
DRAWER_PRO=qute_drawer.pro

all: app doc

app: viewer drawer
	rm qute/Makefile

viewer:
	cd qute && $(QMAKE) $(VIEWER_PRO) && $(MAKE) -f $(MAKEFILE)
	
drawer:
	cd qute && $(QMAKE) $(DRAWER_PRO) && $(MAKE) -f $(MAKEFILE)
	
doc:
	cd help && $(MAKE) -Bsif $(MAKEFILE)