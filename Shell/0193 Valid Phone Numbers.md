```bash
# Read from the file file.txt and output all valid phone numbers to stdout.
# (xxx) xxx-xxxx or xxx-xxx-xxxx

grep -P '^(\(\d{3}\)\s|\d{3}-)\d{3}-\d{4}$' file.txt
```

`grep -P` uses Perl-flavoured regular expression, supporting `\d{n}` to match numbers.
