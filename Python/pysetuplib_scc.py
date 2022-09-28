
    ## This is a general setup file for python scripts written for GRU_Systems Control
    ## This script contains generally reused methods and codes across all scripts written for Systems Control - GRU
    ## Please edit/use the script as deemed necessary. For questions: Authored by - Mohammad Immam (immamma@gru.com)


    ## Imports used in the file
import smtplib  # used email address
import logging
import sys  # to read in command line arguments


from email.message import EmailMessage
from datetime import datetime  # to parse and work with dates
from datetime import timedelta
from xml.etree import ElementTree
from xml.dom import minidom

    ## Setting up the SMPT for email notifications in cases of failure

def SendEmail(text, message_subject):
    text = text + "\n\n\n--------EOD------------ \n PLEASE DO NOT REPLY TO THIS EMAIL!\n" \
                  " IT IS AN AUTO GENERATED EMAIL AND ANY REPLY TO THIS EMAIL WILL NOT REACH ANY USER!\n" \
                  "\n\nGRU SCC TECH SUPPORT\nDL_SCC_TechSupport@gru.com"
    msg = EmailMessage()
    msg.set_content(text)
    msg['Subject'] = message_subject
    msg['From'] = 'SCC_CCOATI01@gru.com'
    msg['To'] = 'SCC_TechSupport@gru.com'
    msg['X-Priority'] = '2'
    s = smtplib.SMTP('grusmtp')
    s.send_message(msg)
    s.quit()

    ## Setting up the logging mechanism

today = datetime.today()  # a variable to hold today as the reference
# configuratuions for all levels
logging.basicConfig(filename=f'Logs/{today.year}-{today.month}-{today.day}_scrlog.txt', level=logging.DEBUG,
                    format='%(asctime)s|%(levelname)s|%(message)s')

# DEBUG: Detailed information, typically of interest only when diagnosing problems.

# INFO: Confirmation that things are working as expected.

# WARNING: An indication that something unexpected happened, or indicative of some problem in the near future (e.g. ‘disk space low’). The software is still working as expected.

# ERROR: Due to a more serious problem, the software has not been able to perform some function.

# CRITICAL: A serious error, indicating that the program itself may be unable to continue running.

# purpose: to write log to file
def Log(level, msg, cntxt="No Context"):
    if level == "WARNING":
        logging.warning(f'{cntxt}|{msg}')
    elif level == "DEBUG":
        logging.debug(f'{cntxt}|{msg}')
    elif level == "INFO":
        logging.info(f'{cntxt}|{msg}')
    elif level == "ERROR":
        logging.error(f'{cntxt}|{msg}')
    elif level == "CRITICAL":
        logging.critical(f'{cntxt}|{msg}')
    else:
        logging.info(f'{cntxt}|wrong log level|{msg}')


    ## Formatting required documents

def prettify_xml(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ElementTree.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")
