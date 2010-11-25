generate.depends = drawer.html
generate.commands = qhelpgenerator drawer.qhp -o drawer.qch
collect.commands = qcollectiongenerator drawer.qhcp -o drawer.qhc
collect.depends = drawer.qhcp

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
