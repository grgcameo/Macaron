import os
import time

# 1. The files and directories to be backed up are
# specified in a list.
# Example on Windows:
#source = ['".\\dir_org"', '.\\dir_back']
source = ['.\\dir_org', '.\\dir_back']
# Example on Mac OS X and Linux:
# source = ['/Users/swa/notes']

# Notice we had to use double quotes inside the string
# for names with spaces in it.


# 2. The backup must be stored in a
# main backup directory
# Example on Windows:
target_dir = '.\\Backup'
# Example on Mac OS X and Linux:
# target_dir = '/Users/swa/backup'
# Remember to change this to which folder you will be using

# 3. The files are backed up into a zip file.  (I use 7z)
# 4. The name of the zip archive is the current date and time
target = target_dir + os.sep + \
    time.strftime('%Y%m%d%H%M%S') + '.7z'


# Create target directory if it is not present

if not os.path.exists(target_dir) :
    os.mkdir(target_dir) #make directory
    
# 5. We use the zip command to put the files in a zip archive
#7z.exe a .\Backup\back.7z .\\dir_org\
zip_command = "7z.exe a {0} {1}".format(target, ' '.join(source))

# Run the backup
print "7z command is:"
print zip_command
print "Running :"

if os.system(zip_command) == 0:
    print 'Successful back to', target
else:
    print 'Backup Failed'



    

