from Grammar import Grammar

class Parser:
    def __init__(self, gr : Grammar):
        self._grammar = gr
        self._firstSet = {}
        self._followSet = {}
        self.generateSets()

    def generateSets(self):
        self.startMyFirst()
        self.startMyFollow()

    def startMyFollow(self):
        startSym = self._grammar.getStartingSymbol()
        self._followSet[startSym]=set("$")

        for nt in self._grammar.getNonTerm():
            if nt != startSym:
                self._followSet[nt]=set()

        for nt in self._grammar.getNonTerm():
            self.myFollow(nt)

    def myFollow(self, nt):
        if nt==self._grammar.getStartingSymbol():
            return
        for p in self._grammar.getProductionContainingNonterminal(nt):
            for rhs in p.getRules():
                if nt in rhs:
                    idx = rhs.index(nt)
                    idx+=1
                    if idx==len(rhs): # then we found nt on the last position
                        self.myFollow(p.getStart())
                        for t in self._followSet[p.getStart()]:
                            self._followSet[nt].add(t)
                    else: # not in the end
                        temporary = []
                        for j in range(idx, len(rhs)):
                            nextSym = rhs[j]
                            copy_first_set = set()
                            for elem in self._firstSet[nextSym]:
                                copy_first_set.add(elem)
                            temporary.append(copy_first_set)
                        res = self.concatForFirst(temporary)
                        if "€" not in res:
                            for r in res:
                                self._followSet[nt].add(r)
                        else:
                            res.remove("€")
                            for r in res:
                                self._followSet[nt].add(r)
                            self.myFollow(p.getStart())
                            for t in self._followSet[p.getStart()]:
                                self._followSet[nt].add(t)


    def startMyFirst(self):
        for t in self._grammar.getTerm(): # init the terminals with themselves
            self._firstSet[t] = t
        for nt in self._grammar.getNonTerm():
            self._firstSet[nt] = set()
        for nt in self._grammar.getNonTerm():
            self.myFirst(nt)

    def concatForFirst(self, temp):
        if len(temp)==1:
            return temp[0]

        res = set()

        has=True
        print(temp)

        for i in range(len(temp)-1):
            for j in range(i+1,len(temp)):
                if "€" not in temp[i] or "€" not in temp[j]:
                    has=False
                for elem1 in temp[i]:
                    for elem2 in temp[j]:
                        if elem1=="€" and elem2!="€":
                            res.add(elem2)
                        elif elem1!="€":
                            res.add(elem1)
        if has:
            res.add("€")

        return res


    def myFirst(self, nt):
        for p in self._grammar.getProductionsForNonterminal(nt):
            for rhs in p.getRules():
                temporary = []
                for elem in rhs:
                    if elem in self._grammar.getTerm() and elem!="€":
                        self._firstSet[nt].add(elem)
                        temporary.append(set(elem))
                    elif elem=="€":
                        self._firstSet[nt].add("€")
                        temporary.append(set("€"))
                    else:
                        self.myFirst(elem)
                        temp = self._firstSet[elem]
                        temporary.append(set(temp))


                res = self.concatForFirst(temporary)
                for e in res:
                    self._firstSet[nt].add ( e )




    def getFirstSet(self):
        return self._firstSet

    def getFollowSet(self):
        return self._followSet

    def getGrammar(self):
        return self._grammar
