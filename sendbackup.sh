zip -r files.zip .
echo Sending mail to $1
mail -s Backup -a files.zip $1 < /dev/null
