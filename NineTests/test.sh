#!/bin/bash

./NineTests > log_output_0

# filter
grep -F -v -f fails.txt  log_output_0 > log_output_1
grep -F -v -f skip.txt   log_output_1 > log_output_2
grep -F -v -f flakes.txt log_output_2 > log_output_final

# remove success, trace and empty lines
grep -v "^succ\|^trace\|^$" log_output_final > log_output_changes

echo "Changes:"
cat log_output_changes

num=$(wc -l < log_output_changes)
echo "Number of changes: $num"

[ -z "$num" ] && exit 2

exit 0
