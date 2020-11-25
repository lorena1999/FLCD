class Production:

    def __init__(self, start, rules):
        self._start = start
        self._rules = rules

    def getRules(self):
        return self._rules

    def getStart(self):
        return self._start

    def __str__(self):
        s = str(self._start)
        s+="\n"
        for r in self._rules:
            s+=str(r)+", "
        return s

