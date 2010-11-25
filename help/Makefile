HELP_GENERATOR=/usr/bin/qhelpgenerator
COLLECTION_GENERATOR=/usr/bin/qcollectiongenerator

all: move
	rm *.qch *.qhc

generate: viewer.html drawer.html
	$(HELP_GENERATOR) viewer.qhp -o viewer.qch && $(HELP_GENERATOR) drawer.qhp -o drawer.qch
    
collect: viewer.qhcp drawer.qhcp
	$(COLLECTION_GENERATOR) viewer.qhcp -o viewer.qhc && $(COLLECTION_GENERATOR) drawer.qhcp -o drawer.qhc
    
make-release:
	-cd ../build/release && mkdir help

make-debug:
	-cd ../build/debug && mkdir help
    
move: generate collect make-release make-debug
	cp *.qch *.qhc ../build/release/help & cp *.qch *.qhc ../build/debug/help
    
