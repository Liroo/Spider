#!/bin/sh

# push to github repository
echo
git push origin master
if [ $? -eq 0 ]
then
  echo
  echo '√ Pushed to github repository'
else
  echo
  echo '✗ Failed to push to github repository'
fi


# push to epitech repository
echo
git push --force git@git.epitech.eu:/romain.gadrat@epitech.eu/cpp_spider master:master
if [ $? -eq 0 ]
then
  echo
  echo '√ Pushed to epitech repository'
else
  echo
  echo '✗ Failed to push to epitech repository'
fi
