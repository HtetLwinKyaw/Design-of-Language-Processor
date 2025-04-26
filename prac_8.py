from collections import defaultdict

# Grammar definition
grammar = {
    "S": [["A", "B", "C"], ["D"]],
    "A": [["a"], ["ε"]],
    "B": [["b"], ["ε"]],
    "C": [["(", "S", ")"], ["c"]],
    "D": [["A", "C"]]
}

first_sets = {
    "S": {"a", "b", "(", "c"},
    "A": {"a", "ε"},
    "B": {"b", "ε"},
    "C": {"(", "c"},
    "D": {"a", "(", "c"}
}

follow_sets = {
    "S": {")", "$"},
    "A": {"b", "(", ")", "$"},
    "B": {"c", ")", "$"},
    "C": {")", "$"},
    "D": {")", "$"}
}

# Construct Predictive Parsing Table
parsing_table = defaultdict(dict)

for non_terminal, productions in grammar.items():
    for production in productions:
        first_symbol = production[0]
        first_set = first_sets[first_symbol] if first_symbol in first_sets else {first_symbol}
        
        for terminal in first_set - {"ε"}:
            parsing_table[non_terminal][terminal] = production
        
        if "ε" in first_set:
            for terminal in follow_sets[non_terminal]:
                parsing_table[non_terminal][terminal] = ["ε"]

# Check if Grammar is LL(1)
def is_ll1():
    for non_terminal, row in parsing_table.items():
        terminals = list(row.keys())
        if len(terminals) != len(set(terminals)):
            return False
    return True

ll1 = is_ll1()

# Validate Input String using the Parsing Table
def validate_string(input_string):
    stack = ["$", "S"]
    index = 0
    input_string += "$"
    
    while stack:
        top = stack.pop()
        
        if top == input_string[index]:
            index += 1
        elif top in parsing_table:
            if input_string[index] in parsing_table[top]:
                rule = parsing_table[top][input_string[index]]
                if rule != ["ε"]:
                    stack.extend(reversed(rule))
            else:
                return "Invalid string"
        elif top == "ε":
            continue
        else:
            return "Invalid string"
    
    return "Valid string" if index == len(input_string) else "Invalid string"

# Output Results
print("Predictive Parsing Table:")
for non_terminal, row in parsing_table.items():
    print(f"{non_terminal}: {row}")

print("\nIs the grammar LL(1)?", "Yes" if ll1 else "No")

# Manual input for string validation
user_input = input("Enter a string to validate: ")
print(f"Input: {user_input} -> {validate_string(user_input)}")