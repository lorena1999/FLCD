import sys
from collections import defaultdict

from Grammar import Grammar

ERR = 'ERR'
POP = 'POP'
ACC = 'ACC'


class Parser:
    def __init__(self, gr: Grammar):
        self._grammar = gr
        self._firstSet = {}
        self._followSet = {}
        self._M = {}
        self.generateSets()

        cell_max_length = 0
        for _ , outer in self._M.items ():
            for _ , inner in outer.items ():
                if len ( str ( inner ) ) > cell_max_length:
                    cell_max_length = len ( str ( inner ) )

        columns_headers = list ( self._grammar.getTerm () - set ( '$' ) ) + ['$']
        row_headers = list ( self._grammar.getNonTerm () ) + list (
            self._grammar.getTerm () - set ( '$' ) ) + ['$']

        cell_max_length += 2

        print ( '   | ' , end='' )
        for column_header in columns_headers:
            print ( column_header , end=' ' * (cell_max_length - 1) )
        print ()
        print ( '---+-' + '-' * cell_max_length * len ( columns_headers ) )
        for row in row_headers:
            print ( row , end='  | ' )
            for column in columns_headers:
                print ( f'{str ( self._M[row][column] ):<{cell_max_length}}' , end='' )
            print ()
        print ( '\n' )

    def generateSets(self):
        self.startMyFirst()
        self.startMyFollow()
        self.generateTable()

    def parseSequence(self, seq):
        stack = ["$"]
        stack.append(self._grammar.getStartingSymbol())

        input = []

        for c in range(len(seq)):
            input.append(seq[c])

        input.append("$")

        input.reverse()

        actions = []

        while len(input)>1 or len(stack)>0:
            currentSym = stack[len(stack)-1]
            top = input[len(input)-1]
            prod = self._M[currentSym][top]
            if prod!=ERR:
                elem = stack.pop()
                if elem == top:
                    input.pop()
                    actions.append(POP)
                else:
                    new_prods = []
                    for i in range(len(prod[1])):
                        new_prods.append(prod[1][i])
                    new_prods.reverse()

                    actions.append(prod)

                    for p in new_prods:
                        if p!="$":
                            stack.append(p)
            else:
                print("Invalid sequence!")
                return

        print("Sequence accepted!")

    def generateTable(self):
        for row in (self._grammar.getNonTerm() | self._grammar.getTerm() | set('$')):
            self._M[row] = defaultdict(lambda: ERR)

        for term in self._grammar.getTerm():
            self._M[term][term] = POP

        self._M['$']['$'] = ACC

        for nonterm in self._grammar.getNonTerm():
            for prod in self._grammar.getProductionsForNonterminal(nonterm):
                for rhs in prod.getRules():
                    firsts = self.getFirstForSequence(rhs, nonterm)
                    for term in (self._grammar.getTerm()):
                        if term in firsts:
                            if self._M[nonterm][term] != ERR:
                                print('Invalid grammar!')
                                print(f'M[{nonterm}][{term}]')
                                print(self._M[nonterm][term])
                                print(nonterm, rhs)
                                sys.exit(-1)
                            else:
                                self._M[nonterm][term] = (nonterm, rhs)

    def getFirstForSequence(self, rhs, st):
        if len(rhs)==1 and rhs[0]=="$":
            return self._followSet[st]

        temp = []
        for elem in rhs:
            temp.append(self._firstSet[elem])
        if temp[0] in self._grammar.getTerm():
            return temp[0]
        res = self.reduceToSet(temp)
        return res

    def startMyFollow(self):
        startSym = self._grammar.getStartingSymbol()
        self._followSet[startSym] = set("$")

        for nt in self._grammar.getNonTerm():
            if nt != startSym:
                self._followSet[nt] = set()

        for nt in self._grammar.getNonTerm():
            self.myFollow(nt, [])

    def myFollow(self, nt, visited):
        for p in self._grammar.getProductionContainingNonterminal(nt):
            for rhs in p.getRules():
                if nt in rhs:
                    if nt in visited:
                        continue
                    idx = rhs.index(nt)
                    idx += 1
                    if idx == len(rhs):  # then we found nt on the last position
                        self.myFollow(p.getStart(), visited + [nt])
                        for t in self._followSet[p.getStart()]:
                            self._followSet[nt].add(t)
                    else:  # not in the end
                        temporary = []
                        for j in range(idx, len(rhs)):
                            nextSym = rhs[j]
                            copy_first_set = set()
                            for elem in self._firstSet[nextSym]:
                                copy_first_set.add(elem)
                            temporary.append(copy_first_set)
                        res = self.reduceToSet(temporary)
                        if "$" not in res:
                            for r in res:
                                self._followSet[nt].add(r)
                        else:
                            res.remove("$")
                            for r in res:
                                self._followSet[nt].add(r)
                            self.myFollow(p.getStart(), visited + [nt])
                            for t in self._followSet[p.getStart()]:
                                self._followSet[nt].add(t)

    def startMyFirst(self):
        for t in self._grammar.getTerm():  # init the terminals with themselves
            self._firstSet[t] = t
        for nt in self._grammar.getNonTerm():
            self._firstSet[nt] = set()
        for nt in self._grammar.getNonTerm():
            self.myFirst(nt, [])

    def reduceToSet(self, temp):
        if len(temp) == 1:
            return set(temp[0])

        res = set()

        hasEpsilon = True

        for i in range(len(temp) - 1):
            for j in range(i + 1, len(temp)):
                if "$" not in temp[i] or "$" not in temp[j]:
                    hasEpsilon = False
                for elem1 in temp[i]:
                    for elem2 in temp[j]:
                        if elem1 == "$" and elem2 != "$":
                            res.add(elem2)
                        elif elem1 != "$":
                            res.add(elem1)
        if hasEpsilon:
            res.add("$")

        return res

    def myFirst(self, nt, visited):
        for p in self._grammar.getProductionsForNonterminal(nt):
            for rhs in p.getRules():
                temporary = []
                for elem in rhs:
                    if elem in visited:
                        continue
                    if elem in self._grammar.getTerm() and elem != "$":
                        self._firstSet[nt].add(elem)
                        temporary.append ( set ( elem ) )
                        break
                    elif elem == "$":
                        self._firstSet[nt].add("$")
                        temporary.append(set("$"))
                    else:
                        self.myFirst(elem, visited + [elem])
                        temp = self._firstSet[elem]
                        temporary.append(set(temp))

                res = self.reduceToSet(temporary)

                for e in res:
                    self._firstSet[nt].add(e)

    def getFirstSet(self):
        return self._firstSet

    def getFollowSet(self):
        return self._followSet

    def getGrammar(self):
        return self._grammar