generate.depends = viewer.html
generate.commands = qhelpgenerator viewer.qhp -o viewer.qch
collect.commands = qcollectiongenerator viewer.qhcp -o viewer.qhc
collect.depends = viewer.qhcp

move.depends = generate collect
move.commands = mv *.qch *.qhc $(TARGET)

docs.depends = move
docs.commands = echo "Documentation built"

QMAKE_EXTRA_TARGETS += generate collect move docs 

CONFIG(debug, debug|release) {
    TARGET = ../build/debug/help
} else {
    TARGET = ../build/release/help
}
