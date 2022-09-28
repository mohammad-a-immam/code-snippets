#!/usr/bin/env python
# coding: utf-8

# # Creating XML Texts & Files

# XML necessary imports for python

# In[8]:


import xml.etree.cElementTree as ET
from xml.etree import ElementTree
from xml.dom import minidom


# Create and form the document

# In[9]:

def prettify(elem):
    """Return a pretty-printed XML string for the Element.
    """
    rough_string = ElementTree.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")

top = ET.Element('root')

comment = ET.Comment('Generated for PyMOTW')
top.append(comment)

child = ET.SubElement(top, 'child')
child.text = 'This child contains text.'

child_with_tail = ET.SubElement(top, 'child_with_tail')
child_with_tail.text = 'This child has regular text.'
child_with_tail.tail = 'And "tail" text.'

child_with_entity_ref = ET.SubElement(top, 'child_with_entity_ref')
child_with_entity_ref.text = 'This & that'


# In[10]:


tree = ET.ElementTree(top)


# Print Test for debugging

# In[11]:



pretty_xml = (prettify(top))
print(pretty_xml)


# In[14]:

with open("somewhere.xml", "w") as f:
    f.write(pretty_xml)




# Your file should now be written to somewhere.xml in the same folder.
