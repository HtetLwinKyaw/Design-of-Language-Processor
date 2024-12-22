class DFA1:
    def __init__(self):
        self.state = 'q0'  # Initial state
        self.transitions = {
            'q0': {'0': 'q1', '1': 'q0'},
            'q1': {'1': 'q2'},
            'q2': {'1': 'q0'},
        }
        self.accepting_states = {'q0'}  # Accepting state
    
    def process(self, string):
        for char in string:
            if char in self.transitions[self.state]:
                self.state = self.transitions[self.state][char]
            else:
                return False  # Invalid transition
        return self.state in self.accepting_states

# Take input from user
input_string_1 = input("Enter a string over 0 and 1 where every 0 is immediately followed by 11: ")
dfa1 = DFA1()
print(f"String '{input_string_1}' is {'accepted' if dfa1.process(input_string_1) else 'rejected'}")
