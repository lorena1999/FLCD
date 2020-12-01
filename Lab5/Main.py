from Grammar import Grammar
from Program import Program
from UI import UI

if __name__ == '__main__':
    grammar = Grammar.read_from_file('g1.txt')
    program = Program(grammar)
    ui = UI(program)
    ui.start()