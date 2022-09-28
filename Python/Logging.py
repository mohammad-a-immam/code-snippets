#!/usr/bin/env python
# coding: utf-8

# In[1]:


#A logging template file in python, please edit and use it as needed


# In[3]:

#imports
import logging


# In[4]:


# DEBUG: Detailed information, typically of interest only when diagnosing problems.

# INFO: Confirmation that things are working as expected.

# WARNING: An indication that something unexpected happened, or indicative of some problem in the near future (e.g. ‘disk space low’). The software is still working as expected.

# ERROR: Due to a more serious problem, the software has not been able to perform some function.

# CRITICAL: A serious error, indicating that the program itself may be unable to continue running.


# Configure the log file, i.e where to log and in what format..
# prepare your dates

# In[6]:

from datetime import datetime

today = datetime.today() #a variable to hold today as the reference

#configuratuions for all levels
logging.basicConfig(filename=f'Logs/{today.year}-{today.month}-{today.day} log.txt', level=logging.DEBUG,
                    format='%(asctime)s|%(levelname)s|%(message)s')


#Defining a simple method to call to write log to file
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


# In[18]:


#if __name__ == '__main__':
Log("WARNING", "Your message here")
Log("WARNING", "Your message here","Context Here")


# In[ ]:




