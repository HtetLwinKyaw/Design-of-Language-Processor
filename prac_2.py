class DFA:
    def __init__(self, states, input_symbols, transition_table, initial_state, accepting_states):
        self.states = states
        self.input_symbols = input_symbols
        self.transition_table = transition_table
        self.initial_state = initial_state
        self.accepting_states = accepting_states

    def process_string(self, input_string):
        current_state = self.initial_state

        for symbol in input_string:
            if symbol not in self.input_symbols:
                return False  # Invalid input symbol
            current_state = self.transition_table[current_state][symbol]

        return current_state in self.accepting_states

# DFA Configuration
states = {1, 2, 3, 4}
input_symbols = {'a', 'b'}
transition_table = {
    1: {'a': 2, 'b': 3},
    2: {'a': 1, 'b': 4},
    3: {'a': 4, 'b': 1},
    4: {'a': 3, 'b': 2}
}
initial_state = 1
accepting_states = {2}


input_str = input("Enter a string to validate: ")

# Instantiate DFA and test string
dfa = DFA(states, input_symbols, transition_table, initial_state, accepting_states)
is_valid = dfa.process_string(input_str)

print(f"The string '{input_str}' is {'valid' if is_valid else 'invalid'}.")



'''
class DFA:
    def __init__(self, num_states, initial_state, accepting_states, transition_table):
        self.num_states = num_states
        self.initial_state = initial_state
        self.accepting_states = accepting_states
        self.transition_table = transition_table
    
    def is_accepting(self, state):
        return state in self.accepting_states
    
    def process_input(self, input_string):
        current_state = self.initial_state
        
        for symbol in input_string:
            if symbol not in self.transition_table[current_state]:
                return False
            current_state = self.transition_table[current_state][symbol]
        
        return self.is_accepting(current_state)

# Define the DFA's transition table
transition_table = {
    1: {'a': 2, 'b': 3},
    2: {'a': 1, 'b': 4},
    3: {'a': 4, 'b': 1},
    4: {'a': 3, 'b': 2}
}

# DFA setup
num_states = 4
initial_state = 1
accepting_states = {2}

# Create DFA object
dfa = DFA(num_states, initial_state, accepting_states, transition_table)

# Test cases
test_cases = [
    ("abbabab", True),  # Valid string example
    ("011", False),  # String over 0 and 1 where every 0 immediately followed by 11
    ("aba", True),  # String over a b c, starts and ends with same letter
    ("a1b", False)  # String over lowercase alphabet and digits, starts with alphabet
]

# Function to test the strings
def test_dfa(dfa, test_cases):
    for input_string, expected in test_cases:
        result = dfa.process_input(input_string)
        print(f"Input: {input_string} => {'Accepted' if result else 'Rejected'} (Expected: {'Accepted' if expected else 'Rejected'})")

# Run the tests
test_dfa(dfa, test_cases)
'''