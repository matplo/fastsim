#!/bin/bash

cdir=$PWD

reponame=sandbox
git clone https://github.com/matplo/$reponame
cd $reponame
git remote rm origin
dir=run2/analyzeESD
#git filter-branch --prune-empty --subdirectory-filter $dir master
git filter-branch --prune-empty --subdirectory-filter $dir -- --all
mkdir $dir
mv * $dir
git add .
git commit .

#git remote rename origin destination
#git remote add origin https://github.com/matplo/pdsftrain
#git remote remove destination
#
#git remote -v

# 2nd part
cd $cdir

git clone https://github.com/matplo/pdsftrain
cd pdsftrain
git remote add repo-A-branch $reponame
git pull repo-A-branch master
git remote rm repo-A-branch

cd $cdir