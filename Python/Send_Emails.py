#!/usr/bin/env python
# coding: utf-8

# # Send Emails

# ### Imports

# In[19]:

import logging #used for logging
import os
import smtplib #used email address
from email.message import EmailMessage


# Setting up the SMPT for email notifications in cases of failure

# In[22]:


def SendEmail(text, message_subject):
    msg = EmailMessage()
    msg.set_content(text)
    msg.set_content(text)
    msg['Subject'] = message_subject
    msg['From'] = 'OatiMachineTest@gru.com' #change this to the email you want the sender to have! EMAIL FROM
    msg['To'] = 'destination@gru.com' #change this to the email address you are sending to.
    msg['X-Priority'] = '2'
    s = smtplib.SMTP('grusmtp')
    s.send_message(msg)
    s.quit()
    


# In[23]:


#if __name__ == '__main__':
SendEmail("Hello Someone, This is a test", "Testing Python Email")



# In[ ]:




