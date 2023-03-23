# Renames a symbol.

import os, sys

if len(sys.argv) < 3:
    print(f"Usage: {sys.argv[0]} [symbol] [new name]")
    sys.exit(0)

original_symbol = sys.argv[1]
new_name = sys.argv[2]

# for each c file in the src folder (recursive search!) and h file in the include folder (recursive search!), replace instances of {original_symbol} with {new_name}.
for root, dirs, files in os.walk("src"):
    for file in files:
        if file.endswith(".c"):
            with open(os.path.join(root, file), "r") as f:
                contents = f.read()
            contents = contents.replace(original_symbol, new_name)
            with open(os.path.join(root, file), "w") as f:
                f.write(contents)

for root, dirs, files in os.walk("include"):
    for file in files:
        if file.endswith(".h"):
            with open(os.path.join(root, file), "r") as f:
                contents = f.read()
            contents = contents.replace(original_symbol, new_name)
            with open(os.path.join(root, file), "w") as f:
                f.write(contents)

with open("config/syms.us.rock_neo.txt", "r") as f:
    contents = f.read()
contents = contents.replace(original_symbol, new_name)
with open("config/syms.us.rock_neo.txt", "w") as f:
    f.write(contents)
