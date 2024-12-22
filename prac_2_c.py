class DFA2:
    def __init__(self):
        self.state = 'q0'  # Initial state
        self.transitions = {
            'q0': {'a': 'qa', 'b': 'qb', 'c': 'qc'},
            'qa': {'a': 'qa', 'b': 'qa', 'c': 'qa'},
            'qb': {'a': 'qb', 'b': 'qb', 'c': 'qb'},
            'qc': {'a': 'qc', 'b': 'qc', 'c': 'qc'},
        }
        self.accepting_states = {'qa', 'qb', 'qc'}  # Accepting states
    
    def process(self, string):
        for char in string:
            if char in self.transitions[self.state]:
                self.state = self.transitions[self.state][char]
            else:
                return False  # Invalid transition
        return string and string[0] == string[-1]

# Take input from user
input_string_2 = input("Enter a string over a, b, c that starts and ends with the same letter: ")
dfa2 = DFA2()
print(f"String '{input_string_2}' is {'accepted' if dfa2.process(input_string_2) else 'rejected'}")
