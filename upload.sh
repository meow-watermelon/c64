#!/bin/bash

# Configuration
FTP_HOST="192.168.1.106"
REMOTE_PATH="/Flash/apps"

# Check if there are any .prg files to upload
ls *.prg >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "No .prg files found in the current directory."
    exit 1
fi

echo "Uploading .prg + .d64 files to $FTP_HOST:$REMOTE_PATH..."

# Use lftp to perform a batch upload
# -c runs the commands and exits
lftp -c "open ftp://$FTP_HOST;
        cd $REMOTE_PATH;
        mput *.prg;
        mput snoopy/*.d64;
        bye"

if [ $? -eq 0 ]; then
    echo "Upload complete!"
else
    echo "Upload failed. Please check your connection to the C64U."
fi
