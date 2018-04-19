#!/bin/bash

file_content=$(cat $1)
echo -e "<DOCTYPE html>\n<head></head><body>" > $1
echo -e "$file_content" >> $1
echo -e "</body>" >> $1
