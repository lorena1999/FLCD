class UI:
    def __init__(self, program):
        self._program = program

    def start(self):
        print("0 - Exit")
        print("1 - Grammar")
        print("2 - Parser")

        option = int(input())

        if option == 0:
            return
        elif option == 1:
            self.fileMenuGrammar()
        elif option == 2:
            self.fileMenuParser()
        else:
            self.start()

    def fileMenuGrammar(self):
        print("0 - Back")
        print("1 - Get non-terminals")
        print("2 - Get terminals")
        print("3 - Get all productions")
        print("4 - Get all production for a specified non-terminal")
        print("5 - Get the initial state")

        option = int(input())
        if option == 0:
            self.start()
        elif option == 1:
            nonTerm = ', '.join(self._program.getNonTerminals())
            print(f'NonTerm = {{{nonTerm}}}')
            self.fileMenuGrammar()
        elif option == 2:
            term = ', '.join(self._program.getGrammar().getTerm())
            print(f'Term = {{{term}}}')
            self.fileMenuGrammar()
        elif option == 3:
            temporary_str_Prod = []
            for key, value in self._program.getGrammar().getProd().items():
                temporary_str_Prod.append(f'\t{key} -> {{{" | ".join(value)}}}')
            strProd = ',\n'.join(temporary_str_Prod)
            print(f'Prod = {{\n'
                  f'{strProd}\n'
                  f'}}')
            self.fileMenuGrammar()
        elif option == 4:
            lhs = input('Enter the nonterminal of the production to print:\n>')
            rhs = self._program.getGrammar().getProd()[lhs]
            print(f'{lhs} -> {{ {" | ".join(rhs)} }}')
            self.fileMenuGrammar()
        elif option == 5:
            print(self._program.getGrammar().getStartingSymbol())
            self.fileMenuGrammar()
        else:
            self.fileMenuGrammar()

    def parseSequence(self, seq):
        self._program.getParseSequence(seq)

    def fileMenuParser(self):
        print("0 - Back")
        print("1 - Get FIRST set")
        print("2 - Get FOLLOW set")
        print("3 - Parse sequence: ")

        option = int(input())
        if option == 0:
            self.start()
        elif option == 1:
            for key, val in self._program.getFirstSet().items():
                self.displaySet(key, val)
            self.fileMenuParser()
        elif option == 2:
            for key, val in self._program.getFollowSet().items():
                self.displaySet(key, val)
            self.fileMenuParser()
        elif option == 3:
            seq = input()
            self.parseSequence(seq)
            self.fileMenuParser()
        else:
            self.fileMenuParser()

    def displaySet(self, key, value):
        s = key + " = { "
        s += ', '.join(value)
        # for symbol in value:
        #     s += symbol + ", "
        s += " }"
        # s.replace(len(s)-3, len(s)-2, "")
        print(s)