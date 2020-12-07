from Parser import Parser


class Program:
    def __init__(self, grammar):
        self._parser = Parser(grammar)

    # Parser stuff
    def getFirstSet(self):
        return self._parser.getFirstSet()

    def getFollowSet(self):
        return self._parser.getFollowSet()

    def getParseSequence(self, seq):
        self._parser.parseSequence(seq)

    # Grammar stuff
    def getGrammar(self):
        return self._parser.getGrammar()

    def getNonTerminals(self):
        return self._parser.getGrammar().getNonTerm()

    def getTerminals(self):
        return self._parser.getGrammar().getTerm()

    def getProductions(self):
        return self._parser.getGrammar().getProductions()

    def getProductionsForNonterminal(self, nonTerminal):
        return self._parser.getGrammar().getProductionsForNonterminal(nonTerminal)

    def getStartingSymbol(self):
        return self._parser.getGrammar().getStartingSymbol()