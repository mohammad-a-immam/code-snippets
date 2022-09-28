# Author Mohammad Immam

# This script copies all file names mentioned in the argument to a folder named pybuild.
# Requirement and Note: The source file and destination files has to be in the same directory as where the script is ran
# Make sure to mention the directory when running the script!

# imports
import sys
import os
import shutil

path = 'build'
commonDirs = ['Logs', 'Error', 'Sent']

# Check whether the specified path exists or not
exists = os.path.exists(path)
print(exists)

if exists:
    print(f"{path} directory exists! replaceing all inside if exists!")
    # for f in os.listdir(path):
    #     os.remove(os.path.join(path, f))
else:
    # Create a new directory because it does not exist
    os.makedirs(path)
    print(f"{path} directory created")

#   Create Log and Error Directory Inside the build

for dir in commonDirs:
    if not os.path.exists(f"{path}/{dir}"):
        os.makedirs(f"{path}/{dir}")

for file in sys.argv:
    if file == __file__:
        continue
    print(f"copying {file} to {path}!")
    shutil.copy(file, f"{path}/{file}")

