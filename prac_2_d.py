class DFA3:
    def __init__(self):
        self.state = 'q0'  # Initial state
        self.transitions = {
            'q0': {char: 'q1' for char in 'abcdefghijklmnopqrstuvwxyz'},  # Alphabet starts
            'q1': {char: 'q1' for char in 'abcdefghijklmnopqrstuvwxyz0123456789'},  # Any valid character
        }
        self.accepting_states = {'q1'}  # Accepting state
    
    def process(self, string):
        for char in string:
            if char in self.transitions[self.state]:
                self.state = self.transitions[self.state][char]
            else:
                return False  # Invalid transition
        return self.state in self.accepting_states

# Take input from user
input_string_3 = input("Enter a string over lowercase alphabet and digits, starting with an alphabet: ")
dfa3 = DFA3()
print(f"String '{input_string_3}' is {'accepted' if dfa3.process(input_string_3) else 'rejected'}")
