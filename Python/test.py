import sys
from datetime import datetime

if len(sys.argv) == 1:
    date = datetime.now
else:
    try:
        date = datetime.strptime(sys.argv[1], '%m/%d/%Y')
    except (ValueError):
        print(f"Invalid argument! Date format not correct. Make sure date is in MM/DD/YYYY format. {ValueError}")


