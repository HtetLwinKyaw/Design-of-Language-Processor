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
                return False  # Invalid input Symbol
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
