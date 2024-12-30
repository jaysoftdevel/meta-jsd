#!/bin/sh

#git filter-branch -f --env-filter "
#    GIT_AUTHOR_NAME='jaysoftdevel'
#    GIT_AUTHOR_EMAIL='jaysoftdevel@gmail.com'
#    GIT_COMMITTER_NAME='jaysoftdevel'
#    GIT_COMMITTER_EMAIL='jaysoftdevel@gmail.com'
#  " HEAD

git config --global user.name "jaysoftdevel"
git config --global user.email "jaysoftdevel@gmail.com"

git rebase -r --root --exec 'git commit --amend --no-edit --reset-author'
