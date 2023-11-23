import os
import datetime
os.system("log.exe")
os.rename("bubble_log.csv", f"bubble_log_{datetime.datetime.now().strftime('%d_%m_%Y_%Hh_%Mm')}.csv")
os.rename("merge_log.csv", f"merge_log_{datetime.datetime.now().strftime('%d_%m_%Y_%Hh_%Mm')}.csv")
os.rename("quick_log.csv", f"quick_log_{datetime.datetime.now().strftime('%d_%m_%Y_%Hh_%Mm')}.csv")