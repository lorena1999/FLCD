import re
from collections import defaultdict
from Grammar import Grammar
from Production import Production

class Parser:
    def __init__(self, gr : Grammar):
        self._grammar = gr
        self._firstSet = {}
        self._followSet = {}
        self.generateSets()

    def getFirstSet(self):
        return self._firstSet

    def getFollowSet(self):
        return self._followSet

    def getGrammar(self):
        return self._grammar

    def generateSets(self):
        self.generateFirstSet() # build the first_set
        self._followSet = self.follow_iterative() # build the follow_set

    def generateFirstSet(self): # start creating the set of FIRST
        for nt in self._grammar.getNonTerm():
            self._firstSet[nt] = self.firstOf(nt) # for each non-terminal assign the specific list of first

    def firstOf(self, nt):
        val = self._firstSet.get(nt, None) # check if there is no other value assigned
        if val!=None:
            return val

        temp = set()
        terminals = set(self._grammar.getTerm())

        for p in self._grammar.getProductionsForNonterminal(nt):
            for rl in p.getRules():
                if rl[0]=="€":
                    temp.add("€")
                for t in rl:
                    firstSymbol = t
                    if firstSymbol in (terminals - set("€")): # just add it and that's it
                        temp.add(firstSymbol)
                    else:
                        res = self.firstOf(firstSymbol) # if it is not a terminal or epsilon, then it must be a non-terminal => find the symbol for the new one (non-terminal)
                        print(res)
                        for r in res: # concatenate the results
                            if r != "€":
                                temp.add(r)

        return temp

    def get_first_terminals(self, non_term:str):
        first_terminals_from_each_production_of_a_non_terminal = []
        values = list(self._grammar.getProd()[non_term])
        for elem in values:
            toks = elem.split(" ")
            if toks[0] in self._grammar.getTerm():
                first_terminals_from_each_production_of_a_non_terminal.append(toks[0])
        return first_terminals_from_each_production_of_a_non_terminal

    def get_first_existing_terminals(self, non_term):
        l=[]
        values = list(self._grammar.getProd()[non_term])
        for elem in values:
            toks = elem.split(" ")
            for tok in toks:
                if tok in self._grammar.getTerm():
                    l.append(tok)
                    break
        return l

    def follow_iterative(self):
        follow_map = self.initialize_for_follow() # create the starting dictionary
        follow_map[self._grammar.getStartingSymbol()].append("$") # append the empty sequence
        while True:
            current_follow_map = self.initialize_for_follow() # create a starting dictionary
            current_follow_map[self._grammar.getStartingSymbol()].append("$") # append empty sequence
            for nt in self._grammar.getNonTerm():
                current_follow_map[nt]+=follow_map[nt]
                prods = self.get_prods_with_nt_in_rhs(nt)# get all the productions that contain non-terminal nt in the rhs
                for key in prods.keys():
                    lhss = prods[key]
                    for lhs in lhss:
                        toks = lhs.split(" ") # get each of the symbols from a production at put them in a list
                        index = toks.index(nt) # get the index where the non-terminal actually is
                        if index == len(toks)-1: # if it is the last one in that production
                            if key!=nt: # if the keys are not the same
                                current_follow_map[nt]+=follow_map[key] # concatenate lists
                        else: # not on the last position
                            first = self.get_first_for_prod(toks[index+1:]) # if there is epsilon in the rhs of that production
                            if "€" in first:
                                first.remove("€")
                                current_follow_map[nt]+=follow_map[key]
                            current_follow_map[nt]+=first

            for key in current_follow_map.keys():
                current_follow_map[key] = set(current_follow_map[key]) # make sure there are no duplicates
            contin = False
            for key in follow_map.keys():
                if len(follow_map[key])!=len(current_follow_map[key]): # while the 2 dicts don't have the same number of production for each key, then continue
                    contin=True
                    break
            if not contin:
                return current_follow_map
            follow_map = current_follow_map

    def concatenate_for_follow(self, l1:list, l2:list): # return concatenation without epsilon
        if "€" in l1:
            l1.remove("€")
            l1+=l2
            return l1
        return l1

    def get_first_for_prod(self, prod):
        result = ["€"]
        contains_terminal = False
        for s in prod:
            first = []
            if s in self._grammar.getTerm():
                first.append(s)
                contains_terminal = True
            else:
                first = self._firstSet[s]
            result = self.concatenate_for_follow(result,first)
            if contains_terminal or "€" in first:
                return list(set(result))
        return list(set(result))

    def get_prods_with_nt_in_rhs(self, nonterminal):
        productions_that_contain_nonterminal = {}
        for key in self._grammar.getProd(): # iterate though all the productions and take the rhs of them
            values = list(self._grammar.getProd()[key]) # init the set of keys in the new dictionary

            for value in values:
                if nonterminal in value: # check non-terminal in rhs
                    if key in productions_that_contain_nonterminal.keys(): # if key already exists, just append the value to the values list
                        productions_that_contain_nonterminal[key].append(value) # add that production
                    else: # if key is inexistent, then create a list formed by one element, that is , value
                        productions_that_contain_nonterminal[key] = [value]
        return productions_that_contain_nonterminal

    def initialize_for_follow(self):
        follow_map = {} # empty dict which will hold as a key non terminal and as a list, the list of follows
        for nt in self._grammar.getNonTerm():
            follow_map[nt] = [] # initialize an empty list for each non terminal
        return follow_map