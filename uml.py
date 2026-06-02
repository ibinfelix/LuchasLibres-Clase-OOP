import os
import glob
from hpp2plantuml import CreatePlantUMLFile

# 1. Gather all header files recursively in your workspace
# This finds both .h and .hpp files in any subdirectory
headers = glob.glob("**/*.hpp", recursive=True) + glob.glob("**/*.h", recursive=True)

if not headers:
    print("No header files (.h or .hpp) found in this directory!")
else:
    print(f"Found {len(headers)} files. Generating UML...")
    # 2. Convert files directly to PlantUML syntax
    CreatePlantUMLFile(headers, "workspace_uml.puml")
    print("Success! Created 'workspace_uml.puml'.")
