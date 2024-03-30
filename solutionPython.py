import re
def read_file(filename):
    with open(filename, 'r') as file:
        data = file.read()
    return data

def remove_excess_space_and_comments(data):
    # Remove comments
    data = re.sub(r'#.*?\n', '', data)
    # Remove excess whitespace
    data = re.sub(r'\s+', ' ', data)
    return data

def tokenize(data):
    # Simple tokenizer
    tokens = re.findall(r'\b\w+\b', data)
    return tokens

def categorize_tokens(tokens):
    keywords = ['def', 'return', 'print']
    operators = ['=', '+']
    delimiters = ['(', ')', ':', ',']
    identifiers = []
    literals = []
    for token in tokens:
        if token in keywords:
            category = 'Keywords'
        elif token in operators:
            category = 'Operators'
        elif token in delimiters:
            category = 'Delimiters'
        elif token.isdigit():
            category = 'Literals'
            literals.append(token)
        else:
            category = 'Identifiers'
            identifiers.append(token)
    return keywords, identifiers, operators, delimiters, literals

def print_code(data):
    print("Cleaned Code:\n", data)

def print_tokens(keywords, identifiers, operators, delimiters, literals):
    print("\nTokenized Code in Tabular Form:")
    print("Category\tTokens")
    print("Keywords\t", ', '.join(keywords))
    print("Identifiers\t", ', '.join(identifiers))
    print("Operators\t", ', '.join(operators))
    print("Delimiters\t", ', '.join(delimiters))
    print("Literals\t", ', '.join(literals))

filename = "filename.txt"  # replace with your file name
data = read_file(filename)
cleaned_data = remove_excess_space_and_comments(data)
tokens = tokenize(cleaned_data)
keywords, identifiers, operators, delimiters, literals = categorize_tokens(tokens)
print_code(cleaned_data)
print_tokens(keywords, identifiers, operators, delimiters, literals)
