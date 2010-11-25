
all: move

generate:
	lrelease ../qute/qute_viewer.pro && lrelease ../qute/qute_drawer.pro
    
make-release:
	-cd ../build/release && mkdir lang

make-debug:
	-cd ../build/debug && mkdir lang
    
move: generate make-release make-debug
	cp *.qm ../build/release/lang && cp *.qm ../build/debug/lang && rm *.qm
    
