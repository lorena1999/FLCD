from Grammar import Grammar

if __name__ == '__main__':
    Gr = Grammar.read_from_file('g2.txt')
    while (res := Gr.run_menu_once()) != '':
        print(res, '\n')
