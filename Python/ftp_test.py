# import subprocess to call your process!
import subprocess
import sys

from pysetuplib_scc import Log, SendEmail
from configparser import ConfigParser
from ftplib import FTP

# Set up the configuration parser
config = ConfigParser()
config.read("inadvertentschedule_props.config")

SUBPROCESS = ["inadvertentschedule_generator.py"]

for item in sys.argv:
    SUBPROCESS.append(item)

# call the required script
process_exitCode = subprocess.call(SUBPROCESS, shell=True)
# check if the process ran as expected!
if process_exitCode != 0:
    # OH NO! IT DID NOT GO RIGHT! NO FTP
    sys.exit(-111)
# print(process_exitCode)

# FTP the generated file to the server
try:
    ftp = FTP(config.get("ftp", "server"))
    ftp.login(config.get("ftp", "user"), config.get("ftp", "password"))

    ftp.cwd("\GVL\LOAD_UPLOAD")

    file = open("gvl_hl.csv", "rb")
    ftp.storbinary("APPE gvl_hl_test_m.csv", file, 1)

    ftp.close()
    Log("INFO", "=== FTP Completed ===", "FTP")
except Exception as e:
    Log("CRITICAL", f"FTP ERROR: {e}", "FTP")
    SendEmail("OATI - FTMS Inadvertent reporting failed on the server, FTP did not complete successfully"
              f"\nError details: {e}.\nScript Name: {__file__}\nLine: (hardcoded) - 36"
              f"\n\nPlease ensure the report is sent over to OATI servers appropriately",
              "FAILURE IN OATI FTMS REPORTING: PLEASE DO NOT REPLY TO THIS EMAIL!")

# END
