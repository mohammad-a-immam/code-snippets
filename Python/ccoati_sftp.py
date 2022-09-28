# gruscc_sftp.py
# Author: Mohammad Immam (immamma@gru.com)


# Description: This is a general python script written to transfer files through SFTP to different destinations. Usages
# include SFTP to EIA and OATI server for different requirements. The process retries 3 times in cases of failures

# requried imports
import logging
import os
import sys
import subprocess
import pysftp
import shutil
import glob
import time
from configparser import ConfigParser
from datetime import datetime  # to parse and work with dates

if len(sys.argv) < 2:
    print("Incorrect Parameters! - Exiting")
    raise IndexError

# Expectations and Inputs
# The script expects paramters:

# name of the config file to use for execution!
configFile = sys.argv[1]

# how many times to try in cases of failure
retries = 3

# configure the logging
today = datetime.today()  # a variable to hold today as the reference
# configuratuions for all levels
logging.basicConfig(filename=f'Logs/{today.year}-{today.month}-{today.day}_scrlog.txt', level=logging.INFO,
                    format='%(asctime)s|%(levelname)s|%(message)s')

config = ConfigParser()
config.read(configFile)

# THE FOLLOWING CONFIGS ARE REQUIRED IN THE CONFIG FILE UNDER 'sftp' SECTION!!!!!!!
# The process to call to generate the file to be sent!
SUBPROCESS = config.get("sftp", "subprocess")
expectedFile = config.get("sftp", "expectedFile")
# SFTP Send details
server = config.get("sftp", "server")
username = config.get("sftp", "username")
password = config.get("sftp", "password")
destination = config.get("sftp", "destination")
filenameBegins = config.get("sftp", "expectedFileWT")

# append any arguments provided
for item in sys.argv:
    if item == __file__ or item == configFile:
        continue
    SUBPROCESS.append(item)

cnopts = pysftp.CnOpts()
cnopts.hostkeys = None
while retries > 0:
    r = str(retries)
    logging.info(f"==== BEGIN TRIAL (backwards count): {str(retries)} ====")
    retries = retries - 1
    try:
        # Call the generator python script
        process_exitCode = subprocess.call(SUBPROCESS, shell=True)
        # check if the process ran as expected!
        if process_exitCode != 0:
            # did not finish successfully
            logging.error(f"generator: {SUBPROCESS} did not complete execution as expected")
        else:
            # file produced. SFTP to the destination server
            with pysftp.Connection(server, username=username, password=password, cnopts=cnopts) as sftp:
                logging.info(f"Connected to SFTP Server: {server} successfully!")
                # where to drop the files
                with sftp.cd(destination):
                    logging.info(f"directory: {destination}")
                    for file in glob.glob(expectedFile):
                        result = sftp.put(file)
                        logging.info(f"SFTP Result: {result}")
                        # SFTP completed! Now Move the files
                        if expectedFile == "GVLDaily*.xml":
                            X = shutil.copy(file, "Sent/")
                        else:
                            x = shutil.copy(file,
                                            "Sent/" + filenameBegins + f"_{today.year}{today.month}{today.day}_{today.hour}.xml")
            logging.info("==== COMPLETED FILE MOVEMENT AND PROCESS ====")
            os.remove(file)
            sys.exit(0)
    except Exception as e:
        logging.error(f"=== Exception Occurred in the SFTP process: {e}. Details: {sys.exc_info()[1]} ===")
        for file in glob.glob(expectedFile):
            if expectedFile == "GVLDaily*.xml":
                shutil.copy(file, "Error/")
            else:
                shutil.copy(file,
                            "Sent/" + filenameBegins + f"_{today.year}{today.month}{today.day}_{today.hour}.xml")
            os.remove(file)
        time.sleep(15)

logging.error("Could not complete in all attempts! Failed Exit!")
sys.exit(1)