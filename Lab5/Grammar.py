import re
from collections import defaultdict
from Production import Production

class Grammar:
    # <editor-fold desc="Constructors">
    def __init__(self, NonTerm: set, Term: set, Prod: dict, Q0: str):
        Grammar._validate_params(NonTerm, Term, Prod, Q0)
        self.NonTerm = NonTerm
        self.Term = Term
        self.Prod = Prod
        self.Q0 = Q0
        self.cuteProductions = []
        self.makeCuteProduction()

    def getProductions(self):
        return self.cuteProductions

    def getProd(self):
        return self.Prod

    def makeCuteProduction(self):
        for key , value in self.Prod.items ():
            newVals = []
            for v in value:
                newVals.append ( v.split () )
            self.cuteProductions.append(Production ( key , newVals ))

    def getProductionsForNonterminal(self, nonterminal):
        productionsForNonterminal = []
        for p in self.cuteProductions:
            if p.getStart() == nonterminal:
                productionsForNonterminal.append(p)
        return productionsForNonterminal

    def getKeysProd(self):
        res = set()
        for p in self.cuteProductions:
            res.add(p.getStart())
        return res

    def getProductionContainingNonterminal(self, nt):
        productionsContainingNt = []
        for p in self.cuteProductions:
            rls = p.getRules()
            for r in rls:
                if nt in r:
                    productionsContainingNt.append(p)
        return productionsContainingNt

    def getStartingSymbol(self):
        return self.Q0

    def getNonTerm(self):
        return self.NonTerm

    def getTerm(self):
        return self.Term

    def getProd(self):
        return self.Prod

    @classmethod
    def read_from_file(cls, filename: str):
        with open(filename, 'r') as infile:
            lines = infile.readlines()
            lines = [line.strip('\n') for line in lines]
            NonTerm = set(lines[0].split(','))
            Term = set(lines[1].split(','))

            Productions_list = [re.split('->', prod_group) for prod_group in lines[2].split('; ')]
            Productions_list = [[prod_group[0], prod_group[1].split('|')] for prod_group in
                                Productions_list]
            Productions_dict = defaultdict(set)
            for productions_group in Productions_list:
                # The first item in each group of productions will be the left side symbol,
                #     and the next items will be the right side symbol
                for prod in productions_group[1]:
                    Productions_dict[productions_group[0]].add(prod)

            Q0 = lines[0].split(',')[0]
            return cls(NonTerm, Term, Productions_dict, Q0)

    # </editor-fold>

    @staticmethod
    def _validate_params(NonTerm: set, Term: set, Prod: dict, Q0: str):
        # Nonterm, Term, and the keys and values of Prod are already guaranteed
        #     to be unique by using sets and dictionaries
        pattern = re.compile('^[A-Za-z0-9€]+$')

        for elem in NonTerm:
            assert pattern.match(elem), f'An element in NonTerm is invalid: {elem}!'

        for elem in Term:
            assert pattern.match(elem), f'An element in Term is invalid: {elem}!'

        for lhs, rhs in Prod.items():
            assert lhs in NonTerm, f'A production in the lhs of the Prod uses an invalid source symbol: {lhs}!'
            for elem in rhs:
                elem_split = elem.split(' ')
                for es in elem_split:
                    assert (es in NonTerm) or (
                                es in Term), f'An element in the rhs of the Production is invalid: {es}!'

    # <editor-fold desc="Pretty Print Helper Functions">
    def _pretty_print_NonTerm(self):
        NoNTerm = ', '.join(self.NonTerm)
        return f'NonTerm = {{ {NoNTerm} }}'

    def _pretty_print_Term(self):
        str_Term = ', '.join(self.Term)
        return f'Term = {{ {str_Term} }}'

    def _pretty_print_all_Prod(self):
        temporary_str_Prod = []

        for key, value in self.Prod.items():
            temporary_str_Prod.append(f'\t{key} -> {{ {" | ".join(value)} }}')
        str_Prod = ',\n'.join(temporary_str_Prod)
        return f'Prod = {{\n' \
               f'{str_Prod}\n' \
               f'}}'

    def _pretty_print_one_Prod(self):
        lhs = input('Enter the nonterminal of the production to print:\n>')
        rhs = self.Prod[lhs]
        return f'{lhs} -> {{ {" | ".join(rhs)} }}'

    def _pretty_print_Q0(self):
        return f'Q0 = {self.Q0}'

    def pretty_print(self, element: str):
        element_to_function = {
            'N': self._pretty_print_NonTerm,
            'T': self._pretty_print_Term,
            'ALLP': self._pretty_print_all_Prod,
            'ONEP': self._pretty_print_one_Prod,
            'Q0': self._pretty_print_Q0,
            }
        return element_to_function[element]()

    # </editor-fold>

    def run_menu_once(self):
        menu = 'Enter N to see the set of non-terminals\n' \
               'Enter T to see the set of terminals\n' \
               'Enter AllP to see the set of productions\n' \
               'Enter OneP to see one of the productions sets\n' \
               'Enter Q0 to see the initial state\n' \
               'Enter X to exit\n' \
               '>'
        user_choice = input(menu).upper()
        if user_choice == 'X':
            print('Bye!')
            return ''
        if user_choice not in ['N', 'T', 'ALLP', 'ONEP', 'Q0']:
            return 'Invalid choice! Please choose one of the 5 given inputs!'
        else:
            return self.pretty_print(user_choice)

    # <editor-fold desc="To String">
    def __str__(self):

        return f'{self.pretty_print("N")}\n' \
               f'{self.pretty_print("T")}\n' \
               f'{self.pretty_print("P")}\n' \
               f'{self.pretty_print("Q0")}'

    __repr__ = __str__
    # </editor-fold>